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
	struct sockaddr_in address = {};
	static int addrLen = sizeof(address);
	address.sin_family = IPV4;
	address.sin_addr.s_addr = ANY_CLIENT;
	address.sin_port = htons(std::strtol(argv[1], NULL, 0));

	if ((connectionFd = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrLen)) < 0) {
		throw std::runtime_error("could not accept connection");
	}

	std::string addr = inet_ntoa(address.sin_addr);
	std::cout << "New client: " << addr << std::endl;

	struct pollfd pfd = {};
	pfd.fd = connectionFd;
	pfd.events = POLLIN;

	for (int ct = 0; ct < 10; ct++) {
		poll(&pfd, 1, -1);

		if (pfd.revents != POLLIN) {
			std::cerr << "client disconnected" << std::endl;
			break;
		}

		char buffer[1024] = {0};
		recv(connectionFd , buffer, 1024, 0);

		std::cout << "From " << addr << ": " << buffer;
		send(connectionFd , "Message received\n" , strlen("Message received\n") , 0 );
	}
	close(connectionFd);
	close(serverFd);
	return 0;
}
