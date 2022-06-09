//
// Created by mlabouri on 6/8/22.
//

#ifndef SOCKSERVER_HPP
#define SOCKSERVER_HPP

#include "ft_irc.hpp"
#include "SockAddress.hpp"

class SockServer {
private:
	std::string _port;
	t_pollfd _serverFd;
	fdVector _fds;
	ipMap	_ips;


public:
	SockServer();
	SockServer(const std::string & port);
	SockServer(const SockServer & src);

	~SockServer();

	SockServer &operator=(const SockServer & src);

	void deleteClient(const fdIterator &  client);
	int check();

	int acceptConnection(SockAddress & addr) const;
	void transmit(int senderFd, const std::string & message, std::basic_ostream<char> & otp);
	std::string readMessage(int fd, bool &err);

	void printStart();

	t_pollfd *getFds();
	size_t getSize();
	int getFd() const;

	fdIterator begin();
	fdIterator end();
};

#endif //SOCKSERVER_HPP
