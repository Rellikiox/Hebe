#include "ConnectionManager.h"

namespace hebe {

	ConnectionManager * ConnectionManager::_instance = NULL;

	ConnectionManager::ConnectionManager(void) {
		next_id = 0;
		socket = boost::asio::ip::udp::socket(io_service);
	}

	ConnectionManager::~ConnectionManager(void) {

	}

	int ConnectionManager::AddLogger(string name, string server, string filename){
		using boost::asio::ip::udp;
	
		int new_id = next_id++;
		udp::endpoint endpoint;

		ServerIter iter = server_endpoint_map.find(server);
		if(iter != server_endpoint_map.end()){
			endpoint = iter->second;
		}else{
			udp::resolver resolver(io_service);
			udp::resolver::query query(udp::v4(), server); 
			endpoint = *resolver.resolve(query);
			server_endpoint_map[server] = endpoint;
			id_endpoint_map[new_id] = endpoint;
		}

		// Envio id con nombre (op_code = 0)

		socket.send_to(getPacket(0, new_id, name), endpoint);

		// Envio id con filename (op_code = 1)

		socket.send_to(getPacket(1, new_id, filename), endpoint);

		return new_id;
	}

	void ConnectionManager::Send(int id, string message){
		
		IdIter iter = id_endpoint_map.find(id);
		if(iter == id_endpoint_map.end())
			return;

		using boost::asio::ip::udp;
		udp::endpoint endpoint = iter->second;
		// Envio id con mensaje (op_code = 2)
		socket.send_to(getPacket(2, id, message), endpoint);
	}
}