#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include <iostream>
#include <map>

class Channels {
	private:
		std::string _name;
		int _creator;
		std::string _topic;
		int	_nbop;
		std::map<int, bool> _members; //Bool pour les opérateurs -> True = Opérator

	public:
		Channels();
		Channels(int creator, std::string name);
		Channels(const Channels& src);
		~Channels();
		Channels &operator=(const Channels& src);

		void setTopic(std::string& mess);
		bool isOper(int fd);

		bool isEmpty();

		void joinChannel(int fd);
		void leaveChannel(int fd);

};


#endif //CHANNELS_HPP
