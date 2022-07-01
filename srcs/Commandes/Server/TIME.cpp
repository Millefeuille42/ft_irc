//Donne l'heure dans le fuseau horaire du serveur
//TIME

#include "../../includes/SockServer.hpp"

void SockServer::time(SockServer &srv, std::vector<std::string> &, User& user) {
	srv.sendMessage(user.fd, TIME(getCurrentTime()) + "\n", std::cout);
}
