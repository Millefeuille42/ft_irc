//Donne les informations du serveur
//INFO

#include "../../includes/SockServer.hpp"

void SockServer::info(SockServer &srv, std::vector<std::string> &, User& user) {
	srv.sendMessage(user.fd, TIME(getCurrentTime()) + "\n", std::cout);
	std::cout.flush();
}
