#include "includes/Channels.hpp"

Channels::Channels() {

}

Channels::Channels(int creator, std::string name, std::string key) : _name(name), _creator(creator), _topic(""), _key(key) {
	_members[creator] = true;
	_nbop = 1;
	initModes();
	if (key != "")
		_modes['k'] = true;
}

Channels::Channels(const Channels& src) {
	*this = src;
}

Channels::~Channels() {
	_members.clear();
}

void Channels::initModes() {
	_modes['i'] = false; //Channel sur Invitation
	_modes['t'] = false; //Topic du Channel modifiable que par les operateurs
	_modes['n'] = false; //Pas de message provenant de l'extérieur
	_modes['l'] = false; //Nombre Maximal de personnes
	_modes['k'] = false; //Clé du Canal

}

std::vector<int> Channels::getUsers() {
	std::vector<int> ret;
	for (std::map<int, bool>::iterator it = _members.begin(); it != _members.end(); it++)
		ret.push_back(it->first);
	return (ret);
}

void Channels::setTopic(std::string &mess) {
	_topic = mess;
}

bool Channels::isOper(int fd) {
	return (_members[fd]);
}

bool Channels::joinChannel(int fd, std::string key) {
	if (_modes['k'] == true && key != _key)
		return (false);
	if (_modes['l'] == true && _members.size() == _maxMembers)
		return (false);
	_members[fd] = false;
	return (true);
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
