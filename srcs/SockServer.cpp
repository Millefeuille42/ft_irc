//
// Created by mlabouri on 6/8/22.
//

#include "includes/SockServer.hpp"

SockServer::SockServer():
_port(), _serverFd(), _fds(), _users() {}

SockServer::SockServer(const std::string & port):
_port(port),
_serverFd(generatePollFd(socketConf(_port.c_str()), DATA_IN)),
_fds(fdVector(0)), _users(userMap()) {
	_fds.push_back(_serverFd);
	printStart();
}

SockServer::SockServer(const SockServer &src) : _serverFd() {
	*this = src;
}

SockServer::~SockServer() {
	for (fdIterator it = _fds.begin(); it != _fds.end(); it++)
		close(it->fd);
}

SockServer &SockServer::operator=(const SockServer &src) {
	if (this == &src)
		return *this;
	for (fdIterator it = _fds.begin(); it != _fds.end(); it++)
		close(it->fd);
	_serverFd = src._serverFd;
	_port = src._port;
	_fds = src._fds;
	_users = src._users;
	return *this;
}

void SockServer::deleteClient(const fdIterator &client) {
	transmit(_users[client->fd], _users[client->fd].nick + " disconnected\n", std::cerr);
	std::cerr.flush();
	_users.erase(client->fd);
	close(client->fd);
	_fds.erase(client);
}

int SockServer::check() {
	// If nothing happened, skip
	if (!_fds.begin()->revents)
		return 0;

	// If event is not incoming data, an error occurred
	if (_fds.begin()->revents != POLLIN) {
		std::cerr << "Error while establishing connexion" << std::endl;
		return 1;
	}

	SockAddress addr = SockAddress(IPV4, ANY_CLIENT, _port.c_str());
	int newFd = acceptConnection(addr);
	_fds.push_back(generatePollFd(newFd, POLLIN));
	_users[newFd] = User(newFd, addr.getIP());

	transmit(_users[newFd], "New connection from: " + addr.getIP() + '\n', std::cerr);
	std::cerr.flush();
	return 1;
}

int SockServer::acceptConnection(SockAddress &addr) const {
	int connectionFd;
	if ((connectionFd = accept(_serverFd.fd, addr.getAddr(), addr.getSize())) < 0) {
		throw std::runtime_error("could not accept connection");
	}
	return connectionFd;
}

void SockServer::transmit(User& user, std::string message, std::basic_ostream<char> & otp) {
	if (!user.nick.empty())
		message = user.nick + ": " + message;
	otp << message;
	for (const_fdIterator it = _fds.begin(); it != _fds.end(); it++) {
		if (it->fd == user.fd || it->fd == _fds.begin()->fd)
			continue;
		send(it->fd, message.c_str(), message.size(), 0);
	}
}

t_pollfd *SockServer::getFds() {
	return _fds.begin().operator->();
}

size_t SockServer::getSize() {
	return _fds.size();
}

fdIterator SockServer::begin() {
	return _fds.begin();
}

fdIterator SockServer::end() {
	return _fds.end();
}

int SockServer::getFd() const {
	return _serverFd.fd;
}

std::string SockServer::readMessage(int fd, bool &err) {
	std::string message;
	size_t ret = BUFFER_SIZE;
	while (ret >= BUFFER_SIZE) {
		err = true;
		char buffer[BUFFER_SIZE + 1] = {0};
		ret = recv(fd, buffer, BUFFER_SIZE, 0);
		buffer[BUFFER_SIZE] = '\0';

		// If message contains data
		if (ret > 0) {
			_users[fd].buffer += buffer;
			if ((_users[fd].buffer).find('\n') != std::string::npos) {
				message = _users[fd].buffer;
				_users[fd].buffer = "";
				err = false;
				break;
			}
			err = false;
		}
	}
	return message;
}

void SockServer::printStart() {
	std::cout << "Started server on port: " << _port << std::endl;
}

void SockServer::messageRouter(int fd, std::string &msg) {
	static std::map<std::string, command> _commands;
	User &usr = _users[fd];
	_commands["PASS"] = pass;
	_commands["NICK"] = nick;
	_commands["USER"] = user;
	_commands["QUIT"] = quit;

	std::vector<std::string> args;
	size_t pos;
	std::string token;
	std::string msgCpy = msg;
	while ((pos = msgCpy.find(' ')) != std::string::npos) {
		token = msgCpy.substr(0, pos);
		args.push_back(token);
		msgCpy.erase(0, pos + 1);
	}
	args.push_back(msgCpy);

	if (_commands.count(args[0])) {
		command tmp = _commands.find(args[0])->second;
		tmp(*this, args, usr);
		return;
	}

	if (!usr.realName.empty()) {
		transmit(usr, msg, std::cout);
		std::cout.flush();
	}
}


