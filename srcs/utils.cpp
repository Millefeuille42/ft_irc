//
// Created by mlabouri on 6/8/22.
//

#include "includes/ft_irc.hpp"
#include <algorithm>

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
