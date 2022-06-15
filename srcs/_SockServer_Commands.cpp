//
// Created by mlabouri on 6/10/22.
//

#include "includes/SockServer.hpp"

static void sendError(int fd, const std::string& err) {
	send(fd, err.c_str(), err.size(), 0);
}

void SockServer::pass(SockServer &srv, std::vector<std::string> args, int fd) {
	if (args.size() < 2) {
		sendError(fd, ERR_NEEDMOREPARAMS(args[0]));
		return;
	}
	if (!srv._users[fd].user.empty()) {
		sendError(fd, ERR_ALREADYREGISTERED);
		return;
	}
	srv._users[fd].pass = args[1];
}

void SockServer::nick(SockServer &srv, std::vector<std::string> args, int fd) {
	if (args.size() > 2 || srv._users[fd].pass != srv.password)
		return;
	if (args.size() < 2) {
		sendError(fd, ERR_NONICKNAMEGIVEN);
		return;
	}
	if (false) { // TODO, user with same name
		sendError(fd, ERR_NEEDMOREPARAMS(args[0]));
		return;
	}
	if (false) { // TODO, Wrong characters
		sendError(fd, ERR_ERRONEUSNICKNAME(args[1]));
		return;
	}
	srv._users[fd].nick = args[1];
}

void SockServer::user(SockServer &srv, std::vector<std::string> args, int fd) {
	//if (srv._users[fd].pass != srv.password)
	//	return;
	if (args.size() < 5) {
		sendError(fd, ERR_NEEDMOREPARAMS(args[0]));
		return;
	}
	if (!srv._users[fd].user.empty()) {
		sendError(fd, ERR_ALREADYREGISTERED);
		return;
	}
	srv._users[fd].user = args[1];
	srv._users[fd].realName = args[4];
}

void SockServer::quit(SockServer &srv, std::vector<std::string>, int fd) {
	close(fd);
	srv._users.erase(fd);
	for (fdIterator it = srv.begin(); it != srv.end(); it++) {
		if (it->fd == fd) {
			srv.deleteClient(it);
			break;
		}
	}
}
