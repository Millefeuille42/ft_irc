//
// Created by mlabouri on 6/7/22.
//

#ifndef SOCKADDRESS_HPP
#define SOCKADDRESS_HPP

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <string>

class SockAddress {
public:
	SockAddress();
	SockAddress(const SockAddress & src);
	SockAddress(sa_family_t family, in_addr_t address, char *port);

	~SockAddress();

	struct sockaddr *getAddr();
	std::string getIP();

	socklen_t *getSize();

	SockAddress & operator=(const SockAddress & src);

public:

private:
	struct sockaddr_in addr;
	size_t size;
};


#endif //SOCKADDRESS_HPP
