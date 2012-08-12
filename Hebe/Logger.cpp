#include "Logger.h"
#include "ConnectionManager.h"

namespace hebe {

	Logger::Logger(void) {
		cm = NULL;
		id = -1;
	}

	Logger::~Logger(void) {
		cm = NULL;
		id = -1;
	}

	Logger::Logger(string logger_name, string server_address, string filename) {
		cm = ConnectionManager::getInstance();
		id = cm->AddLogger(logger_name, server_address, filename);
	}
	
	Logger::Logger(const Logger &l) {
		cm = l.cm;
		id = l.id;
	}

	Logger & Logger::operator=(const Logger &l) {
		if(this != &l){
			cm = l.cm;
			id = l.id;
		}
	}

	void Logger::Log(string message) {
		cm->Send(id, message);
	}
}