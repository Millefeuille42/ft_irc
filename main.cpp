#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <poll.h>

#include "User.hpp"
#include <vector>
#include <map>

//* struct sockaddr_in {
//short   sin_family;       /* la famille de protocole */
//u_short sin_port;         /* numéro de port */
//struct  in_addr sin_addr; /* adresse IP de la machine */
//char    sin_zero[8];      /* remplissage pour faire 16 octets */
//};

void	printProut(const int &new_socket, std::string buffer, std::string& from) {
	//std::cout << std::string(buffer) << std::endl;
	//send(new_socket, "prout", strlen("prout"), 0);
	if (buffer == "ping\n")
		send(new_socket, "pong\n", strlen("pong\n"), 0);
	if (buffer == "Bye\n") {
		send(new_socket, "Bye !\n", strlen("Bye !\n"), 0);
		close(new_socket);
		exit(EXIT_SUCCESS);
	}
}

int main(int ac, char **av) {
	struct sockaddr_in address;
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr << "Socket Failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Setsockopt" << std::endl;
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET; //Protocole IPv4
	address.sin_addr.s_addr = INADDR_ANY; //0.0.0.0
	address.sin_port = htons(8080); //TODO -> av[1]

	if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::cerr << "Bind Failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 3) < 0) {
		std::cerr << "Listen" << std::endl;
		exit(EXIT_FAILURE);
	}

	typedef std::vector<struct pollfd> victor;
	typedef std::map<int, User> pmap;

	victor paulVictor = victor(0);
	pmap paulMap = pmap();

	struct pollfd paul;
	paul.fd = sockfd;
	paul.events = POLLIN;

	paulVictor.push_back(paul);

	while (42) {
		poll(&(*paulVictor.begin()), paulVictor.size(), -1);

		victor::iterator it = paulVictor.begin();
		if (it->revents == POLLIN) {
			int new_socket;
			int addrlen = sizeof(address);
			if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
				std::cerr << "Accept" << std::endl;
				exit(EXIT_FAILURE);
			}
			paul.fd = new_socket;
			paulVictor.push_back(paul);
			paulMap.insert(std::pair<int, User>(paul.fd, User(paul.fd)));
		}
		it++;
		for ( ; it != paulVictor.end(); it++) {
			if (it->revents == POLLIN) {
				char buffer[200] = {0};
				recv(it->fd, buffer, 199, 0);
				if (paulMap[it->fd].getFirst() == 0)
					paulMap[it->fd].setName(std::string(buffer));
				else {
					std::string from = paulMap[it->fd].getName();
					victor::iterator it2 = paulVictor.begin();
					it2++;
					for (; it2 != paulVictor.end(); it2++)
						printProut(it2->fd, std::string(buffer), from);
				}
			}
		}
	}
	return (0);
}