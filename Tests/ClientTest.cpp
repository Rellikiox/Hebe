#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_service io_service;

		udp::socket socket(io_service, udp::endpoint(udp::v4(), 9000));

		for (;;)
		{
			std::vector<boost::asio::const_buffer> recv_buf;
			udp::endpoint remote_endpoint;
			boost::system::error_code error;
			while(true){
				std::cout << "Waiting for a message..." << std::endl;
				socket.receive_from(boost::asio::buffer(recv_buf),
					remote_endpoint, 0, error);

				if (error && error != boost::asio::error::message_size)
					throw boost::system::system_error(error);
				std::cout << "Message received: " << std::endl;

				std::cout << recv_buf.size() << std::endl;

				//for(int i = 0; i < recv_buf.size(); i++){
				//	std::cout << recv_buf[i];
				//}
				//std::cout << std::endl;
			}
			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;
			socket.send_to(boost::asio::buffer(message),
				remote_endpoint, 0, ignored_error);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

/*

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
try
{
boost::asio::io_service io_service;

udp::resolver resolver(io_service);
udp::resolver::query query(udp::v4(), "localhost", "daytime");
udp::endpoint receiver_endpoint = *resolver.resolve(query);

udp::socket socket(io_service);
socket.open(udp::v4());

boost::array<char, 4> send_buf  = { 'p', 'a', 't', 'o' };
socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

boost::array<char, 128> recv_buf;
udp::endpoint sender_endpoint;
size_t len = socket.receive_from(
boost::asio::buffer(recv_buf), sender_endpoint);

std::cout.write(recv_buf.data(), len);
}
catch (std::exception& e)
{
std::cerr << e.what() << std::endl;
}

system("pause");

return 0;
}

*/