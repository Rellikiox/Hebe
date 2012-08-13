#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <map>

using namespace std;

namespace hebe {

	class HebeServer {
	public:
		HebeServer(void);
		~HebeServer(void);

		void Start(unsigned short port);

		bool Run();

		void Stop();

	private:
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint endpoint;

		struct Packet{
			string GetMessageString(){
				string result;
				for(int i = 0; i < message_length; i++){
					result.push_back(message[i]);
				}
				return result;
			}

			int op_code;
			int id;
			boost::array<char, 256> message;
			int message_length;
		};
		/*
		typedef boost::array<boost::asio::, 3> Packet;
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
		}*/
	};

}