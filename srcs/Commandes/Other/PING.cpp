//Tester la présence d'un client actif
//PING <serveur1> [<serveur2>]

#include "../../includes/SockServer.hpp"

void SockServer::ping(SockServer &srv, std::vector<std::string> &, User& user) {
	srv.sendMessage(user.fd, "PONG ircserv\n", std::cout);
	std::cout.flush();
}
