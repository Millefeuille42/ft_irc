//
// Created by mlabouri on 6/7/22.
//

#include "includes/SockAddress.hpp"

SockAddress::SockAddress() : addr(), size(sizeof(addr)) {}

SockAddress::SockAddress(const SockAddress &src): addr(), size(sizeof(addr)) {
	*this = src;
}

SockAddress::SockAddress(sa_family_t family, in_addr_t address, char *port)
	: addr(), size(sizeof(addr)) {
	addr.sin_family = family;
	addr.sin_addr.s_addr = address;
	addr.sin_port = htons(std::strtol(port, NULL, 0));
}

SockAddress::~SockAddress() {}

SockAddress &SockAddress::operator=(const SockAddress &src) {
	if (this != &src)
		addr = src.addr;
	return *this;
}

struct sockaddr *SockAddress::getAddr() {
	return reinterpret_cast<sockaddr *>(&addr);
}

socklen_t *SockAddress::getSize() {
	return reinterpret_cast<socklen_t *>(&size);
}

std::string SockAddress::getIP() {
	return inet_ntoa(addr.sin_addr);
}
