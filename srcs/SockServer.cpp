//
// Created by mlabouri on 6/8/22.
//

#include "includes/SockServer.hpp"

SockServer::SockServer():
_port(), _serverFd(), _fds(), _users(), _nicks(), _chans() {}

SockServer::SockServer(const std::string & port):
_port(port),
_serverFd(generatePollFd(socketConf(_port.c_str()), DATA_IN)),
_fds(fdVector(0)), _users(userMap()), _nicks(stringVector(0)), _chans(channelsMap()) {
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
	_fds.clear();
	_users.clear();
	_nicks.clear();
	_chans.clear();
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
	if (!_users[client->fd].nick.empty())
		std::cerr << _users[client->fd].nick + ": disconnected" << std::endl;
	else
		std::cerr << _users[client->fd].ip + ": disconnected" << std::endl;
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
	if (password.empty())
		_users[newFd] = User(newFd, addr.getIP(), 1);
	else
		_users[newFd] = User(newFd, addr.getIP());

	//transmit(_users[newFd], "New connection from: " + addr.getIP() + '\n', std::cerr);
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

void SockServer::sendMessage(int target, const std::string & message, std::basic_ostream<char> & otp) {
	otp << "\tSENT -> " << message;
	otp.flush();
	send(target, message.c_str(), message.size(), 0);
}

void SockServer::sendMessage(int target, const std::string & message) {
	send(target, message.c_str(), message.size(), 0);
}

void SockServer::transmit(User& user, std::string message, std::basic_ostream<char> & otp) {
	if (!user.nick.empty())
		message = user.nick + ": " + message + "\n";
	else
		message = user.ip + ": " + message + "\n";
	otp << "\tSENT -> "<< message;
	otp.flush();
	for (const_fdIterator it = _fds.begin(); it != _fds.end(); it++) {
		if (it->fd == user.fd || it->fd == _fds.begin()->fd)
			continue;
		sendMessage(it->fd, message);
	}
}

void SockServer::transmitServ(std::string& message) {
	std::cerr << "\tSENT -> " << message;
	std::cerr.flush();
	for (const_fdIterator it = _fds.begin(); it != _fds.end(); it++) {
		if (it->fd == _fds.begin()->fd) {
//			if (it + 1 == _fds.end()) //S'il n'y a plus de clients, le serveur recevra tout de même le message.
//				std::cerr << message; jsp pk c'est lq
			continue;
		}
		sendMessage(it->fd, message);
	}
}

void SockServer::transmitToChannel(Channels &chan, const User &user, const std::string& message) {
	std::cout << message;
	std::cout.flush();
	std::vector<int> users = chan.getUsers();
	for (std::vector<int>::iterator it = users.begin(); it != users.end(); it++) {
		if (*it == user.fd)
			continue;
		sendMessage(*it, message);
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

User *SockServer::getUserByNick(const std::string &nick) {
	for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->second.nick == nick)
			return &it->second;
	}
	return NULL;
}

User *SockServer::getUserByRealName(const std::string &realname) {
	for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->second.realName == realname)
			return &it->second;
	}
	return NULL;
}

User *SockServer::getUserByUsername(const std::string &username) {
	for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->second.user == username)
			return &it->second;
	}
	return NULL;
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
			size_t nlPos = (_users[fd].buffer).find('\n');
			if (nlPos != std::string::npos) {
				message = _users[fd].buffer.substr(0, (int)nlPos);
				std::string tmp = _users[fd].buffer.substr(nlPos + 1, std::string::npos);

				size_t vPos = message.find('\r');
				if (vPos != std::string::npos)
					message.erase(vPos);

				_users[fd].buffer = tmp;
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
	_commands["QUIT"] = quit;
	//_commands["MODE"] = mode;
	_commands["OPER"] = oper;

	//_commands["INVITE"] = invite;
	_commands["JOIN"] = join;
	//_commands["KICK"] = kick;
	//_commands["LIST"] = list;
	//_commands["MODE"] = mode;
	//_commands["NAMES"] = names;
	//_commands["PART"] = part;
	//_commands["TOPIC"] = topic;

	_commands["PRIVMSG"] = privmsg;

	//_commands[ERROR] = error;
	_commands["KILL"] = kill;
	_commands["PING"] = ping;

	//_commands["WHO"] = who;

	_commands["INFO"] = info;
	_commands["TIME"] = time;
	_commands["VERSION"] = version;
}

// TODO	Error messages on commands

void SockServer::messageRouter(int fd, std::string &msg) {
	User &usr = _users[fd];
	
	std::vector<std::string> args = parseMessage(msg);
	if ((usr.nick.empty() || usr.user.empty()) && (args[0] != "USER" || args[0] != "NICK") ) {
		if (usr.pass == 0 && args[0] != "PASS")
			return;
	}
	std::transform(args[0].begin(), args[0].end(),args[0].begin(), ::toupper);
	std::string disp = usr.ip;
	if (!usr.nick.empty())
		disp = usr.nick;
	std::cout << "[" << args[0] << "] - " << disp << std::endl;
	if (args[0] == usr.nick + ':')
		args.erase(args.begin());

	if (_commands.count(args[0])) {
		command tmp = _commands.find(args[0])->second;
		tmp(*this, args, usr);
		return;
	}
}
