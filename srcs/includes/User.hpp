//
// Created by mlabouri on 6/10/22.
//

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
	User();
	User(int gFd, const std::string & gIp);
	User(const User& src);

	~User();

	User &operator=(const User &src);

public:
	std::string user;
	std::string realName;
	std::string nick;
	std::string pass;
	std::string ip;
	std::string buffer;
	int fd;
};


#endif //USER_HPP
