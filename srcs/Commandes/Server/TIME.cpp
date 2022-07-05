//Donne l'heure dans le fuseau horaire du serveur
//TIME

#include "../../includes/SockServer.hpp"

void SockServer::time(SockServer &, std::vector<std::string> &, User& user) {
	sendMessage(user.fd, TIME(user.nick, getCurrentTime()) + "\n", std::cout);
}
