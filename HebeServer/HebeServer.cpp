#include "HebeServer.h"

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
			

			/*
			boost::array<int,1> op_code(boost::asio::buffer_cast<boost::array<int, 1> >(recv_buf[0]));
			boost::array<int,1> id(boost::asio::buffer_cast<boost::array<int, 1> >(recv_buf[1]));
			//boost::array<int,1> message(boost::asio::buffer_cast<char *>(recv_buf[2]));

			std::cout << "op_code: " << op_code[0] << endl;
			std::cout << "id: " << id[0] << endl;*/
		}
	}

	void HebeServer::Stop(){
		socket.close();
	}
}