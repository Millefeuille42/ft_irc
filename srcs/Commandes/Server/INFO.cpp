//Donne les informations du serveur
//INFO

#include "../../includes/SockServer.hpp"

void SockServer::info(SockServer &srv, std::vector<std::string> &, User& user) {
	sendMessage(user.fd, INFO(user.nick, std::string("Time: ") + getCurrentTime()) + "\n", std::cout);
	sendMessage(user.fd, INFO(user.nick, std::string("Version: ") + getVersion()) + "\n", std::cout);
	std::ostringstream ss(""); ss << "Members: " << srv._fds.size();
 	sendMessage(user.fd, INFO(user.nick, ss.str()) + "\n", std::cout);
	ss.str(""); ss << "Port: " << srv._port;
	sendMessage(user.fd, INFO(user.nick, ss.str()) + "\n", std::cout);
	sendMessage(user.fd, std::string(ENDOFINFO(user.nick)) + "\n", std::cout);
}
