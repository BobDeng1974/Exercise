#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

void SOCK();

int main(int argc, char* argv[]){
	SOCK();
	return 0;
}

void SOCK() {
	io_service iosev;

	boost::system::error_code ec;
	ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 0);

	for (int port = 1; port <= 1200; port++) {
		ip::tcp::socket socket(iosev);
		ep.port(port);
		socket.connect(ep, ec);

		std::cout << port << ' ';
		if (ec) {
			std::cout << boost::system::system_error(ec).what() << std::endl;
			continue;
		}
		else {
			std::cout << "succeed" << std::endl;
		}

		socket.close();
	}
}
