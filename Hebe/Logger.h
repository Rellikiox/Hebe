#pragma once

#include <string>
using namespace std;

namespace hebe {

	class ConnectionManager;

	class Logger {
	public:
		Logger(void);
		~Logger(void);
		Logger(string logger_name, string server_address, string filename);
		Logger(const Logger &l);
		Logger & operator=(const Logger &l);

		void Log(string message);
	private:
		ConnectionManager *cm;
		int id;
	};

}