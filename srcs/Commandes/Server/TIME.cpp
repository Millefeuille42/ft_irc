//Donne l'heure dans le fuseau horaire du serveur
//TIME

#include "../../includes/SockServer.hpp"

void SockServer::time(SockServer &srv, std::vector<std::string> &, User& user) {
	//std::time_t t = std::time(NULL);
	//std::tm* now = std::localtime(&t);

	srv.sendMessage(user.fd, "PONG\n", std::cout);
	std::cout.flush();
}
