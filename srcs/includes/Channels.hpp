#ifndef CHANNELS_HPP
#define CHANNELS_HPP

#include "includes/ft_irc.hpp"

class Channels {
	private:
		std::string _name;
		int _creator;
		std::string _topic;
		std::map<int, bool> _members; //Bool pour les opérateurs -> True = Opérator

	public:
		Channels();
		Channels(int creator, std::string name);
		Channels(const Channels& src);
		~Channels();
		Channels &operator=(const Channels& src);

		void setTopic(std::string& mess);
		bool isOper(int fd);

		void joinChannel(int fd);
		void leaveChannel(int fd);

};


#endif //CHANNELS_HPP
