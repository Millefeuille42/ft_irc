//
// Created by mlabouri on 6/10/22.
//

#include "includes/SockServer.hpp"

//static void sendError(int fd, const std::string& err) {
//	send(fd, err.c_str(), err.size(), 0);
//}
//

void SockServer::pass(SockServer &srv, std::vector<std::string> args, User& user) {
	(void)srv;
	(void)args;
	(void)user;
}

void SockServer::nick(SockServer &srv, std::vector<std::string> args, User& user) {
	(void)srv;
	(void)args;
	(void)user;
}

void SockServer::user(SockServer &srv, std::vector<std::string> args, User& user) {
	(void)srv;
	(void)args;
	(void)user;
}

void SockServer::quit(SockServer &srv, std::vector<std::string>, User& user) {
	(void)srv;
	(void)user;
}
