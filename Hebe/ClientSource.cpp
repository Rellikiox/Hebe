

#include "Logger.h"

#include <iostream>

using namespace std;


int main(void) {

	hebe::Logger log("logger_1", "127.0.0.1", 9000, "pruebas.txt");

	log.Log("potato");

	return 0;
}