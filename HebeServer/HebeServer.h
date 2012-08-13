#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <map>
#include <queue>
#include <fstream>

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
			time_t timestamp;
		};

		map<int, string> id_name_map;
		typedef map<int, string>::iterator StringMapIter;
		map<int, string> id_filename_map;

		map<int, queue<Packet> > unprocesed_packets;

		void ProcessPacket(Packet p);
		void NewUser(Packet p);
		void NewFile(Packet p);
		void LogMessage(Packet p);
	};

}