#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include <iostream>
#include <map>

class Channels {
	private:
		std::string _name;
		int _creator;
		std::string _topic;
		std::string _key;
		int	_nbop;
		std::map<int, bool> _members; //Bool pour les opérateurs -> True = Opérator

	public:
		Channels();
		Channels(int creator, std::string name, std::string key);
		Channels(const Channels& src);
		~Channels();
		Channels &operator=(const Channels& src);

		void setTopic(std::string& mess);
		bool isOper(int fd);

		bool isEmpty();

		bool joinChannel(int fd, std::string key);
		void leaveChannel(int fd);

};


#endif //CHANNELS_HPP
