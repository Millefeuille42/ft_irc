//
// Created by mlabouri on 6/7/22.
//

#ifndef SOCKADDRESS_HPP
#define SOCKADDRESS_HPP

#include "ft_irc.hpp"

class SockAddress {
public:
	SockAddress();
	SockAddress(const SockAddress & src);
	SockAddress(sa_family_t family, in_addr_t address, const char *port);

	~SockAddress();

	SockAddress & operator=(const SockAddress & src);

	struct sockaddr *getAddr();
	std::string getIP();

	socklen_t *getSize();


public:

private:
	struct sockaddr_in _addr;
	size_t size;
};


#endif //SOCKADDRESS_HPP
