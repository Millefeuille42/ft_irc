#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include <iostream>
#include <map>
#include <vector>

class User;

class Channels {
	private:
		std::string _name;
		int _creator;
		std::string _topic;
		std::string _key;
		int	_nbop;
		size_t _maxMembers;
		std::map<int, bool> _members; //Bool pour les opérateurs -> True = Opérator
		std::map<char, bool> _modes;
		//std::vector<int> _fdBans;

	public:
		Channels();
		Channels(int creator, std::string name, std::string key);
		Channels(const Channels& src);
		~Channels();
		Channels &operator=(const Channels& src);

		void initModes();

		std::vector<int> getUsers();

		std::string getName();
		void setTopic(std::string& mess);
		bool isOper(int fd);

		bool isEmpty();

		bool joinChannel(int fd, std::string key);
		void leaveChannel(int fd);

		void oMode(char ar, User *user); //Rendre Operateur le user; (Vérifier si User est NULL)
		//void bMode(char ar, User *user); //Ban le user;
		void lMode(char ar, int nb = 0); //Nombre limites de Users possibles
		void kMode(char ar, std::string key = ""); //Mettre une clé pour entrer dans le channel
		void allModes(char ar, char mode);
};

#include "User.hpp"

#endif //CHANNELS_HPP
