#include "User.hpp"
#include "Server.hpp"
#include <poll.h>
#include <vector>

int main(int ac, char **av) {

	typedef std::vector<struct pollfd> victor;
	victor paulVictor = victor(0);
	Server serv(8080, "pass");

	struct pollfd paul;
	paul.fd = serv.getFd();
	paul.events = POLLIN;

	paulVictor.push_back(paul);

	while (42) {
		poll(&(*paulVictor.begin()), paulVictor.size(), -1);
		victor::iterator it = paulVictor.begin();
		if (it->revents == POLLIN) {
			paul.fd = serv.addUser();
			paulVictor.push_back(paul);
		}
		else {
			for (it = paulVictor.begin()++ ; it != paulVictor.end(); it++) {
				if (it->revents == POLLIN) {
					serv.rMessage(it->fd);
				}
			}
		}
	}
	return (0);
}