#pragma once

#ifndef NULL
#define NULL 0
#endif

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <map>

using namespace std;

namespace hebe {

	class ConnectionManager {
	public:
		static ConnectionManager * getInstance() {
			if(_instance == NULL){
				_instance = new ConnectionManager();
			}
			return _instance;
		}
		~ConnectionManager(void);

		int AddLogger(string name, string server, unsigned short port, string filename);

		void Send(int id, string message);

	private:
		static ConnectionManager * _instance;
		ConnectionManager(void);
		

		struct Packet{
			Packet(int o, int i, string m) : op_code(o), id(i) {
				message_length = m.size() <= 256 ? m.size() : 256;
				for(int i = 0; i < message_length; ++i){
						message[i] = m[i];
				}
			}
			int op_code;
			int id;
			boost::array<char,256> message;
			int message_length;
		};
		/*
		typedef boost::array<boost::asio::mutable_buffer, 3> Packet;
		Packet getPacket(int o, int i, string m){
			boost::array<int,1> op_code = { o };
			boost::array<int,1> id		= { i };
			char message[256];
			strcpy(message, m.c_str());
			Packet p = {
				boost::asio::buffer(op_code),
				boost::asio::buffer(id),
				boost::asio::buffer(message) };

			return p;
		}
		*/

		map<string, boost::asio::ip::udp::endpoint> server_endpoint_map;
		typedef map<string, boost::asio::ip::udp::endpoint>::iterator ServerIter;

		map<int, boost::asio::ip::udp::endpoint> id_endpoint_map;
		typedef map<int, boost::asio::ip::udp::endpoint>::iterator IdIter;

		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		int next_id;
	};

}