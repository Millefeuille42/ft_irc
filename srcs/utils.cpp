//
// Created by mlabouri on 6/8/22.
//

#include "includes/ft_irc.hpp"

struct pollfd generatePollFd(int fd, short events) {
	struct pollfd ret = {};
	ret.fd = fd;
	ret.events = events;
	return ret;
}
