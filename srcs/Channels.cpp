#include "includes/Channels.hpp"

Channels::Channels() {

}

Channels::Channels(int creator, std::string name) : _name(name), _creator(creator), _topic("") {
	_members[creator] = true;
	_nbop = 1;
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
	if (_members[fd] == true) {
		if (_nbop == 1 && _members.size() != 1) { //Si plus d'operateur, un op est definit de maniere random. Si plus personne, le channel est perdu.
			if (_members.begin()->first == fd)
				_members.begin()++->second  = true;
			else
				_members.begin()->second = true;
			_nbop++;
		}
		_nbop--;
	}
	_members.erase(fd);
}

bool Channels::isEmpty() {
	return (_members.empty());
}

Channels& Channels::operator=(const Channels& src) {
	_name = src._name;
	_topic = src._topic;
	_creator = src._creator;
	_members = src._members;

	return *this;
}
