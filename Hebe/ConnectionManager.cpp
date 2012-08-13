#include "ConnectionManager.h"

namespace hebe {

	ConnectionManager * ConnectionManager::_instance = NULL;

	ConnectionManager::ConnectionManager(void) : socket(io_service), next_id(0) {
		socket.open(boost::asio::ip::udp::v4());
	}

	ConnectionManager::~ConnectionManager(void) {
		socket.close();
	}

	int ConnectionManager::AddLogger(string name, string server, unsigned short port, string filename){
		using boost::asio::ip::udp;

		int new_id = next_id++;
		udp::endpoint endpoint;

		ServerIter iter = server_endpoint_map.find(server);
		if(iter != server_endpoint_map.end()){
			endpoint = iter->second;
		}else{
			endpoint = udp::endpoint(boost::asio::ip::address::from_string(server), port);

			server_endpoint_map[server] = endpoint;
			id_endpoint_map[new_id] = endpoint;
		}

		//boost::array<char, 1> send_buf  = { 'p' };
		//socket.send_to(boost::asio::buffer(send_buf), endpoint);
		
		Packet p(0,new_id, name);

		// Envio id con nombre (op_code = 0)
		socket.send_to(boost::asio::buffer(&p, sizeof(p)), endpoint);
		
		// Envio id con filename (op_code = 1)

		Packet p2(1, new_id, filename);
		socket.send_to(boost::asio::buffer(&p2, sizeof(p2)), endpoint);

		return new_id;
	}

	void ConnectionManager::Send(int id, string message){

		IdIter iter = id_endpoint_map.find(id);
		if(iter == id_endpoint_map.end())
			return;

		using boost::asio::ip::udp;
		udp::endpoint endpoint = iter->second;
		Packet p(2, id, message);
		// Envio id con mensaje (op_code = 2)
		socket.send_to(boost::asio::buffer(&p, sizeof(p)), endpoint);
	}
}