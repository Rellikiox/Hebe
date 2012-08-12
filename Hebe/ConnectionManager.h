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

		int AddLogger(string name, string server, string filename);

		void Send(int id, string message);

	private:
		static ConnectionManager * _instance;
		ConnectionManager(void);

		struct Packet{
			Packet(int o, int i, string m) : op_code(o), id(i), message(m.c_str()) {}
			boost::array<boost::asio::mutable_buffer, 3> getPacket() {
				boost::array<int, 1> o = { op_code };
				boost::array<int, 1> i = { id };
				//boost::array<char, 512> m = message;
				boost::array<boost::asio::mutable_buffer, 3> p = {
					boost::asio::buffer(o),
					boost::asio::buffer(i),
					boost::asio::buffer(message)};
			}

			int op_code;
			int id;
			boost::array<char, 256> message;
		};
	};

}