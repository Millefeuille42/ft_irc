#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include <iostream>
#include <map>
#include <vector>

class User;

#define ALL_GOOD 0
#define NO_MEMBER 1
#define LAST_OPER 2
#define WRONG_DECLARATION 3


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
		Channels(int creator, const std::string& name, const std::string& key);
		Channels(const Channels& src);
		~Channels();
		Channels &operator=(const Channels& src);

		void initModes();

		std::vector<int> getUsers();

		std::string getKey();
		size_t getMaxMembers();
		std::string getName();
		void setTopic(std::string& mess);
		std::string getTopic();
		bool isOper(int fd);

		bool isEmpty();
		bool isMode(char mode);

		int joinChannel(int fd, const std::string& key);
		void joinChannel(int fd);
		int leaveChannel(int fd);

		int oMode(char ar, User *user); //Rendre Operateur le user; (Vérifier si User est NULL)
		int lMode(char ar, int nb = 0, const std::string& snb = ""); //Nombre limites de Users possibles
		int kMode(char ar, const std::string& key = ""); //Mettre une clé pour entrer dans le channel
		void allModes(char ar, char mode);
};

#include "User.hpp"

#endif //CHANNELS_HPP
