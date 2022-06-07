//
// Created by mlabouri on 6/3/22.
//

#include <arpa/inet.h>
#include "includes/ft_irc.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	int serverFd = socketConf(argv[1]);
	int connectionFd;

	SockAddress addr = SockAddress(IPV4, ANY_CLIENT, argv[1]);

	if ((connectionFd = accept(serverFd, addr.getAddr(), addr.getSize())) < 0) {
		throw std::runtime_error("could not accept connection");
	}

	std::cout << "New client: " << addr.getIP() << std::endl;

	struct pollfd pfd = {};
	pfd.fd = connectionFd;
	pfd.events = POLLIN;

	for (int ct = 0; ct < 10; ct++) {
		poll(&pfd, 1, -1);

		if (pfd.revents != POLLIN) {
			std::cerr << addr.getIP() + " disconnected" << std::endl;
			break;
		}

		std::string response = "Message received\n";

		char buffer[1024] = {0};
		int ret = recv(connectionFd , buffer, 1024, 0);
		if (ret > 0) {
			std::cout << "From " << addr.getIP() << ": " << buffer;
			std::cout.flush();
		}
		send(connectionFd, response.c_str(), response.size(), 0);
	}
	close(connectionFd);
	close(serverFd);
	return 0;
}
