#pragma once

#ifndef NULL
#define NULL 0
#endif

#include <boost\asio.hpp>
#include <string>

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
	};

}