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
		Packet recv_buf;
		udp::endpoint remote_endpoint;
		boost::system::error_code error;
		while(true){
			std::cout << "Waiting for a message..." << std::endl;
			socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);
			
			std::cout << "Message received: " << std::endl;
			std::cout << recv_buf.size() << std::endl;
		}
	}

	void HebeServer::Stop(){
		socket.close();
	}
}