#include "includes/Channels.hpp"

Channels::Channels() {

}

Channels::Channels(int creator, std::string name) : _name(name), _creator(creator), _topic("") {
	_members[creator] = true;
}

Channels::Channels(const Channels& src) {
	*this = src;
}

Channels::~Channels() {
	_members.clear();
}

void Channels::setTopic(std::string &mess) {
	_topic = mess;
}

bool Channels::isOper(int fd) {
	return (_members[fd]);
}

void Channels::joinChannel(int fd) {
	_members[fd] = false;
}

void Channels::leaveChannel(int fd) {

}

Channels& Channels::operator=(const Channels& src) {
	_name = src._name;
	_topic = src._topic;
	_creator = src._creator;
	_members = src._members;

	return *this;
}
