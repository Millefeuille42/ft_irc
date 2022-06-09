//
// Created by mlabouri on 6/3/22.
//

#include <cerrno>
#include "includes/SockServer.hpp"
#include "includes/SockAddress.hpp"

void catchSig(int sig) {
	std::cout << "Caught signal " << sig << " Exiting..." << std::endl;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	SockServer server = SockServer(argv[1]);
	signal(SIGTERM, catchSig);
	signal(SIGINT, catchSig);
	signal(SIGKILL, catchSig);
	signal(SIGHUP, catchSig);

	while (true) {
		int acNum = poll(server.getFds(), server.getSize(), -1);
		if (acNum == -1) {
			if (errno == EINTR)
				break;
			std::cerr << "Error on poll" << std::endl;
			break;
		}

		// Check if server has a new connection
		if (server.check())
			acNum--;

		for (fdIterator it = server.begin(); it != server.end(); it++) {
			if (acNum <= 0)
				break;
			// If nothing happened, skip
			if (!it->revents || it->fd == server.getFd())
				continue;

			// If there is data to read
			if (it->revents == POLLIN) {
				acNum--;
				bool err;
				std::string msg = server.readMessage(it->fd, err);
				if (!err)
					continue;
			}

			// If there is an error OR the message is empty, client disconnected
			fdVector::iterator nxt = it - 1;
			server.deleteClient(it);
			it = nxt;
		}
	}
	std::cout << "Bye!" << std::endl;
}
