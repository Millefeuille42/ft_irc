//
// Created by mlabouri on 6/10/22.
//

#include "includes/User.hpp"

User::User() : user(), realName(), nick(), pass(), ip(), buffer(), fd(0) {}

User::User(int gFd, const std::string &gIp)
	: user(), realName(), nick(), pass(), ip(gIp), buffer(), fd(gFd) {}

User::User(const User &src) {
	*this = src;
}

User::~User() {}

User &User::operator=(const User &src) {
	if (this != &src) {
		user = src.user;
		nick = src.nick;
		pass = src.pass;
		ip = src.ip;
		buffer = src.buffer;
		fd = src.fd;
		realName = src.realName;
	}
	return *this;
}
