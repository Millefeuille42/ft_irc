//
// Created by mlabouri on 6/10/22.
//

#include "includes/User.hpp"

User::User() : user(), realName(), nick(), pass(0), ip(), buffer(), fd(0) {
	initModes();
}

User::User(int gFd, const std::string &gIp, bool s_pass)
	: user(), realName(), nick(), pass(s_pass), ip(gIp), buffer(), fd(gFd) {
	initModes();
}

User::User(const User &src) {
	*this = src;
}

User::~User() {
	modes.clear();
}

User &User::operator=(const User &src) {
	if (this != &src) {
		user = src.user;
		nick = src.nick;
		pass = src.pass;
		ip = src.ip;
		buffer = src.buffer;
		fd = src.fd;
		realName = src.realName;
		modes = src.modes;
	}
	return *this;
}

void User::initModes() {
	modes["a"] = false; //Flagged as Away
	modes["i"] = false; //Invisible
	modes["o"] = false; //Operator Flag
}
