//
// Created by mlabouri on 6/10/22.
//

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>
#include "Channels.hpp"

class User {
public:
	User();
	User(int gFd, const std::string & gIp, bool s_pass = 0);
	User(const User& src);

	~User();

	User &operator=(const User &src);

	void enterChannel(Channels* chan, bool op);
	void leaveChannel(Channels* chan);

	void initModes();

public:
	std::string user;
	std::string realName;
	std::string nick;
	bool pass;
	std::string ip;
	std::string buffer;
	int fd;
	std::map<Channels*, bool> channels;
	std::map<std::string, bool> modes;
};


#endif //USER_HPP
