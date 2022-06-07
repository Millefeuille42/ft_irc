//
// Created by mlabouri on 6/3/22.
//

#include "includes/ft_irc.hpp"

int acceptConnection(int serverFd, SockAddress addr) {
	int connectionFd;
	if ((connectionFd = accept(serverFd, addr.getAddr(), addr.getSize())) < 0) {
		throw std::runtime_error("could not accept connection");
	}
	return connectionFd;
}

struct pollfd generatePollFd(int fd, short events) {
	struct pollfd ret = {};
	ret.fd = fd;
	ret.events = events;
	return ret;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	int serverFd = socketConf(argv[1]);
	t_pollVector pollVector = t_pollVector(0);

	pollVector.push_back(generatePollFd(serverFd, POLLIN));

	// TODO get IP of client
	for (;true;) {
		t_pollVector::iterator serverPoll = pollVector.begin();
		poll(serverPoll.operator->(), pollVector.size(), -1);

		t_pollVector vecBuffer = t_pollVector(0);
		for (t_pollVector::iterator it = serverPoll; it != pollVector.end(); it++) {
			if (!it->revents)
				continue;
			if (it->revents != POLLIN) {
				std::cout << "Error on FD " << it->fd << std::endl;
				// TODO Close and Erase fd
				continue;
			}
			if (it->fd == serverPoll->fd) {
				SockAddress addr = SockAddress(IPV4, ANY_CLIENT, argv[1]);
				int newFd = acceptConnection(serverFd, addr);
				vecBuffer.push_back(generatePollFd(newFd, POLLIN));
				std::cout << "New connection" << std::endl;
				continue;
			}
			std::string response = "Message received\n";
			char buffer[1024] = {0};
			int ret = recv(it->fd, buffer, 1024, 0);
			if (ret > 0) {
				std::cout << "Message: " << buffer;
				std::cout.flush();
			}
			send(it->fd, response.c_str(), response.size(), 0);
		}
		for (t_pollVector::iterator it = vecBuffer.begin(); it != vecBuffer.end(); it++) {
			pollVector.push_back(*it);
		}
	}
}
