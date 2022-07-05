//Donne la version du serveur
//VERSION

#include "../../includes/SockServer.hpp"

void SockServer::version(SockServer &, std::vector<std::string> &, User& user) {
	sendMessage(user.fd, VERSION(user.nick, getVersion()) + "\n", std::cout);
}
