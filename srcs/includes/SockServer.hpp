//
// Created by mlabouri on 6/8/22.
//

#ifndef SOCKSERVER_HPP
#define SOCKSERVER_HPP

#include "ft_irc.hpp"
#include "SockAddress.hpp"
#include "_SockServer_Errors.hpp"


class SockServer {
private:
	typedef void(*command)(SockServer &, std::vector<std::string>, User&);
	std::string _port;
	t_pollfd _serverFd;
	fdVector _fds;
	userMap _users;
	stringVector _nicks;

public:
	SockServer();
	SockServer(const std::string & port);
	SockServer(const SockServer & src);

	~SockServer();

	SockServer &operator=(const SockServer & src);

	void deleteClient(const fdIterator &  client);
	int check();

	int acceptConnection(SockAddress & addr) const;
	void transmit(User& user, std::string message, std::basic_ostream<char> & otp);
	std::string readMessage(int fd, bool &err);

	void messageRouter( int fd, std::string &msg);

	void printStart();

	t_pollfd *getFds();
	size_t getSize();
	int getFd() const;
	stringVector& getNicks();

	fdIterator begin();
	fdIterator end();

	static void pass(SockServer &srv, std::vector<std::string>, User& user);
	static void user(SockServer &srv, std::vector<std::string>, User& user);
	static void nick(SockServer &srv, std::vector<std::string>, User& user);
	static void quit(SockServer &srv, std::vector<std::string>, User& user);

	std::string password;
};

#endif //SOCKSERVER_HPP
