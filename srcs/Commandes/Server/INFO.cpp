//Donne les informations du serveur
//INFO

#include "../../includes/SockServer.hpp"

void SockServer::info(SockServer &srv, std::vector<std::string> &, User& user) {
	srv.sendMessage(user.fd, INFO(std::string("Time: ") + getCurrentTime()) + "\n", std::cout);
	srv.sendMessage(user.fd, INFO(std::string("Version: ") + getVersion()) + "\n", std::cout);
	std::ostringstream ss(""); ss << "Members: " << srv._fds.size();
 	srv.sendMessage(user.fd, INFO(ss.str()) + "\n", std::cout);
	ss.str(""); ss << "Port: " << srv._port;
	srv.sendMessage(user.fd, INFO(ss.str()) + "\n", std::cout);
	srv.sendMessage(user.fd, std::string(ENDOFINFO) + "\n", std::cout);
	std::cout.flush();
}
