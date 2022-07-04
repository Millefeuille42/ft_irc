#include "includes/Channels.hpp"

Channels::Channels() {
}

Channels::Channels(int creator, std::string name, std::string key) : _name(name), _creator(creator), _topic(""), _key(key) {
	_members = std::map<int, bool>();
	_modes = std::map<char, bool>();
	_members[creator] = true;
	std::cout << _members.begin()->first << std::endl;
	_nbop = 1;
	initModes();
	if (key != "") {
		kMode('+', key);
	}
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
	for (std::map<int, bool>::iterator it = _members.begin(); it != _members.end(); it++) {
		std::cout << it->first << std::endl;
		ret.push_back(it->first);
	}
	return (ret);
}

void Channels::setTopic(std::string &mess) {
	_topic = mess;
}

bool Channels::isOper(int fd) {
	return (_members[fd]);
}

std::string Channels::getName() {
	return (_name);
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
	_topic = src._topic;
	_key = src._key;
	_nbop = src._nbop;
	_maxMembers = src._maxMembers;
	_modes = src._modes;
	//_fdBans = src._fdBans;

	return *this;
}

std::string Channels::oMode(char ar, User *user) {
	if (user == NULL || _members.find(user->fd) == _members.end())
		return ("Member not find"); //Membre Introuvable dans le Channel
	if (ar == '+') {
		_members[user->fd] = true;
		user->channels[this] = true;
		return (user->nick + " is now operator in the channel " + _name);
	}
	else if (ar == '-') {
		_members[user->fd] = false;
		user->channels[this] = false;
		return (user->nick + " is not an operator in the channel " + _name);
	}
	return ("");
}

//TODO un peu la flemme de faire le ban, comme lors de la déco il faudrait deban comme je pensais le faire avec les fd
//Chiant et long pour rien.
//void Channels::bMode(char ar, User *user) {
//	if (user == NULL)
//		return ; //Membre Introuvable
//	if (ar == '+' && _members.find(user->fd) != _members.end()) {
//		_fdBans.push_back(user->fd);
//		leaveChannel(user->fd); //Rajouter un message de ban ?
//	}
//	else if (ar == '-') {
//		std::find(_fdBans.begin(), user->fd);
//	}
//}

std::string Channels::lMode(char ar, int nb, std::string snb) {
	if (ar == '+') {
		_modes['l'] = true;
		_maxMembers = nb;
		return ("Limit member on the channel " + _name + " is now " + snb);
	}
	else if (ar == '-') {
		_modes['l'] = false;
		return ("There is no limit member on the channel " + _name);
	}
	return ("");
}

std::string Channels::kMode(char ar, std::string key) {
	if (ar == '+') {
		_modes['k'] = true;
		_key = key;
		return ("Channel " + _name + " is protected by a key");
	}
	else if (ar == '-') {
		_modes['k'] = false;
		return ("Channel " + _name + " is not protected by a key");
	}
	return ("");
}


void Channels::allModes(char ar, char mode) {
	if (ar == '+')
		_modes[mode] = true;
	else if (ar == '-')
		_modes[mode] = false;
}
