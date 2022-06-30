//Donne la version du serveur
//VERSION

#include "../../includes/SockServer.hpp"

void SockServer::version(SockServer &srv, std::vector<std::string> &, User& user) {
	srv.sendMessage(user.fd, VERSION(getVersion()) + "\n", std::cout);
	std::cout.flush();
}
