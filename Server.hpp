#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "User.hpp"
#include <map>

class Server {
	private :
		int _port;
		std::string _password;
		int _fd;
		struct sockaddr_in _address;
		std::map<int, User> _paulMap;

	public :
		Server();
		Server(int port, std::string password);
		Server(const Server& src);
		Server& operator=(const Server& src);
		~Server();

		int	getFd() const;
		int addUser();
		void	rMessage(int fd);
		void	sMessage(int fd, std::string mess, std::string from);

};


#endif
