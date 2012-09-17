#include "HebeServer.h"

#include <ctime>

namespace hebe {
	using boost::asio::ip::udp;

	HebeServer::HebeServer(void) : socket(io_service) {
	}

	HebeServer::~HebeServer(void) {
	}

	void HebeServer::Start(unsigned short port){
		socket.open(udp::v4());
		endpoint = udp::endpoint(udp::v4(), port);
		socket.bind(endpoint);
	}		

	bool HebeServer::Run(){
		//Packet recv_buf;
		Packet recv_buf;
		udp::endpoint remote_endpoint;
		boost::system::error_code error;
		while(true){
			std::cout << "Waiting for a message..." << std::endl;
			size_t len = socket.receive_from(boost::asio::buffer(&recv_buf, sizeof(recv_buf)), remote_endpoint, 0, error);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);

			std::cout << "Message received from: " << remote_endpoint << std::endl;
			std::cout << "Content: " << std::endl;
			std::cout << "Operation: " << recv_buf.op_code << std::endl;
			std::cout << "Identifier: " << recv_buf.id << std::endl;
			std::cout << "Message: " << recv_buf.GetMessageString() << std::endl;

			ProcessPacket(recv_buf);
		}
	}

	void HebeServer::Stop(){
		socket.close();
	}

	void HebeServer::ProcessPacket(Packet p){
		switch (p.op_code){
		case 0:	// ID-Username	
			NewUser(p);
			break;
		case 1:	// ID-filename
			NewFile(p);
			break;
		case 2:	// ID-Message
			LogMessage(p);
			break;
		default:
			break;
		}
	}

	void HebeServer::NewUser(Packet p){
		StringMapIter iter = id_name_map.find(p.id);
		if(iter == id_name_map.end()){
			id_name_map[p.id] = p.GetMessageString();
		}
	}

	void HebeServer::NewFile(Packet p){
		StringMapIter iter = id_filename_map.find(p.id);
		if(iter == id_filename_map.end()){
			id_filename_map[p.id] = p.GetMessageString();
		}
	}

	void HebeServer::LogMessage(Packet p){ 
		StringMapIter name_iter = id_name_map.find(p.id);
		StringMapIter file_iter = id_filename_map.find(p.id);
		if(name_iter != id_name_map.end() && file_iter != id_filename_map.end()) { // User found and has file
			fstream f;
			f.open(id_filename_map[p.id].c_str(), ios::out);

			f << "[" << p.id << "]" << p.GetMessageString() << endl;

			f.close();
		}else{	// User not found or doesn't have a file
			unprocesed_packets[p.id].push(p);
		}
	}
}