
#include "HebeServer.h"


int main(void){

	hebe::HebeServer server;

	server.Start(9000);

	server.Run();

	server.Stop();

	return 0;
}