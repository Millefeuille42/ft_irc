//
// Created by mlabouri on 6/8/22.
//

#include "includes/SockServer.hpp"

struct pollfd generatePollFd(int fd, short events) {
	struct pollfd ret = {};
	ret.fd = fd;
	ret.events = events;
	return ret;
}

std::vector<std::string> parseMessage(std::string msg) {
	std::vector<std::string> args;
	size_t pos;
	std::string token;
	while ((pos = msg.find(' ')) != std::string::npos) {
		token = msg.substr(0, pos);
		args.push_back(token);
		msg.erase(0, pos + 1);
	}
	args.push_back(msg);
	return args;
}

void SockServer::welcome(SockServer& srv, const std::vector<std::string>&, User& user) {
	if (user.nick.empty() || user.user.empty())
		return;
	srv.sendMessage(user.fd, WELCOME(user.nick, user.user) + "localhost\n", std::cout);
	std::cout.flush();
}

std::string getCurrentTime() {
	std::time_t t = std::time(NULL);
	std::tm* now = std::localtime(&t);
	std::ostringstream ss("");

	ss << now->tm_mday << '-'
			<< (now->tm_mon + 1) << '-'
			<< (now->tm_year + 1900) << " - "
			<< now->tm_hour << ':'
			<< now->tm_min << ':'
			<< now->tm_sec;
	return ss.str();
}

std::string getVersion() {
	std::ifstream versionFile;
	versionFile.open("version.txt", std::ios::out);
	if (!versionFile.is_open()) {
		std::cerr << std::strerror(errno) << std::endl;
		return "N/A";
	}

	std::string ret;
	getline(versionFile, ret);
	versionFile.close();
	if (ret.empty())
		return "N/A";
	return ret;
}
