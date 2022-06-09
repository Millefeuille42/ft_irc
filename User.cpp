#include "User.hpp"

User::User() {

}

User::User(const User& src) {
	*this = src;
}

User& User::operator=(const User& src) {
	_name = src._name;
	_fd = src._fd;
	_first = src._first;

	return (*this);
}

User::User(int& fd) : _fd(fd), _first(1) {
	send(_fd, "What's your name ?\n", strlen("What's your name ?\n"), 0);
}

User::~User() {
	close(_fd);
}

bool User::getFirst() const {
	return (_first);
}

void User::setName(std::string n) {
	_name = n;
	_first = 0;
}

const std::string& User::getName() const {
	return _name;
}
