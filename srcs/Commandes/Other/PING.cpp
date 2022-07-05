//Tester la présence d'un client actif
//PING <serveur1> [<serveur2>]

#include "../../includes/SockServer.hpp"

void SockServer::ping(SockServer &, std::vector<std::string> &args, User& user) {
	if (args.size() < 2) {
		sendMessage(user.fd, ERR_NOORIGIN(user.nick), std::cout);
		return;
	}
	sendMessage(user.fd, "PONG ircserv\n", std::cout);
}
