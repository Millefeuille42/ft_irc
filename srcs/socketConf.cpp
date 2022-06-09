//
// Created by mlabouri on 6/3/22.
//

#include "includes/ft_irc.hpp"

static int startSocket() {
	int serverFd;
	if ((serverFd = socket(IPV4, TCP, IP_PROTOCOL)) <= 0) {
		throw std::runtime_error("socket creation failed");
	}

	int opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				   &opt, sizeof(opt))) {
		throw std::runtime_error("socket was not properly created");
	}

	return serverFd;
}

static void bindSocket(int serverFd, const char *port) {
	struct sockaddr_in address = {};
	static int addrLen = sizeof(address);
	address.sin_family = IPV4;
	address.sin_addr.s_addr = ANY_CLIENT;
	address.sin_port = htons(std::strtol(port, NULL, 0));

	if (bind(serverFd, (struct sockaddr *)&address,addrLen) < 0) {
		throw std::runtime_error("socket bind failed");
	}
}

int socketConf(const char *port) {
	int serverFd = startSocket();
	bindSocket(serverFd, port);
	if (listen(serverFd, MAX_CLIENTS)) {
		throw std::runtime_error("socket listen failed");
	}
	std::cout << "Socket up" << std::endl;
	return serverFd;
}
