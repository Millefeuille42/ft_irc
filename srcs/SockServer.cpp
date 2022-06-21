//
// Created by mlabouri on 6/8/22.
//

#include "includes/SockServer.hpp"

SockServer::SockServer():
_port(), _serverFd(), _fds(), _users(), _nicks() {}

SockServer::SockServer(const std::string & port):
_port(port),
_serverFd(generatePollFd(socketConf(_port.c_str()), DATA_IN)),
_fds(fdVector(0)), _users(userMap()), _nicks(stringVector(0)) {
	_fds.push_back(_serverFd);
	initCommands();
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
	for (stringVector::iterator it = _nicks.begin(); it != _nicks.end(); it++) {
		if (_users[client->fd].nick == *it) {
			_nicks.erase(it);
			break ;
		}
	}
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
	if (password == "")
		_users[newFd] = User(newFd, addr.getIP(), 1);
	else
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

stringVector& SockServer::getNicks() {
	return (_nicks);
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

void SockServer::initCommands() {
	_commands["PASS"] = pass;
	_commands["NICK"] = nick;
	_commands["USER"] = user;
	//_commands["QUIT"] = quit;
	//_commands["MODE"] = mode;
	//_commands["OPER"] = oper;

	//_commands[INVITE] = invite;
	//_commands[JOIN] = join;
	//_commands[KICK] = kick;
	//_commands[LIST] = list;
	//_commands[MODE] = mode;
	//_commands[NAMES] = names;
	//_commands[PART] = part;
	//_commands[TOPIC] = topic;

	//_commands[PRIVMSG] = privmsg;

	//_commands[ERROR] = error;
	//_commands[KILL] = kill;
	//_commands[PING] = ping;
	//_commands[PONG] = pong;

	//_commands[WHO] = who;

	//_commands[INFO] = info;
	//_commands[TIME] = time;
	//_commands[VERSION] = versions;
}

void SockServer::messageRouter(int fd, std::string &msg) {
	User &usr = _users[fd];

	std::vector<std::string> args = parseMessage(msg);

	if (usr.pass == 0 && args[0] != "PASS")
		return;
	if (usr.nick.empty() && usr.user.empty() && (args[0] != "USER" || args[0] != "NICK") )
		return;

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
