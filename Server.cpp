#include "Server.hpp"

Server::Server() {

}

Server::Server(int port, std::string password) : _port(port), _password(password) {
	if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr << "Socket Failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	int opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Setsockopt" << std::endl;
		exit(EXIT_FAILURE);
	}

	_address.sin_family = AF_INET; //Protocole IPv4
	_address.sin_addr.s_addr = INADDR_ANY; //0.0.0.0
	_address.sin_port = htons(_port);
	if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
		std::cerr << "Bind Failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(_fd, 400) < 0) {
		std::cerr << "Listen" << std::endl;
		exit(EXIT_FAILURE);
	}

	_paulMap = std::map<int, User>();

}

Server::Server(const Server& src) {

}

Server& Server::operator=(const Server &src) {
	_fd = src._fd;
	_port = src._port;
	_password = src._password;
	_address = src._address;
	_paulMap = src._paulMap;

	return (*this);
}

Server::~Server() {

}

int Server::getFd() const {
	return (_fd);
}

int Server::addUser() {
	int new_socket;
	int addrlen = sizeof(_address);
	if ((new_socket = accept(_fd, (struct sockaddr *)&_address, (socklen_t*)&addrlen)) < 0) {
		std::cerr << "Accept" << std::endl;
		exit(EXIT_FAILURE);
	}
	User newUser(new_socket);
	_paulMap.insert(std::pair<int, User>(new_socket, newUser));
	return (new_socket);
}

void Server::rMessage(int fd) {
	char buffer[1024] = {0};
	recv(fd, buffer, 199, 0);
	if (_paulMap[fd].getFirst() == 1)
		_paulMap[fd].setName(std::string(buffer));
	else {
		for (std::map<int, User>::iterator it = _paulMap.begin() ; it != _paulMap.end(); it++)
			sMessage(it->first, std::string(buffer), _paulMap[fd].getName());
	}
}

void Server::sMessage(int fd, std::string mess, std::string from) {
	 std::string text(from + " : " + mess);
	 send(fd, text.c_str(), text.length(), 0);
}