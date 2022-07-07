//Modifier ou voir le sujet d'un canal
//TOPIC <canal> [<sujet>]

#include "../../includes/SockServer.hpp"

void SockServer::topic(SockServer &srv, std::vector<std::string> &args, User &user) {
	if (args.size() < 2 && args[0] != "topic") {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick, args[0])) + "\n", std::cerr);
		return;
	}
	if (!cInSet(args[1][0], "#&+!")) {
		std::cerr << "Not a channel";
		return ;
	}
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);
	if (chan == srv._chans.end()) {
		sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cerr);
		return;
	}
	if (!user.channels.count(&chan->second)) {
		sendMessage(user.fd, std::string(ERR_NOTONCHANNEL(user.nick, chan->first)) + "\n", std::cerr);
		return;
	}
	if (chan->second.isMode('t') && chan->second.isOper(user.fd) == false) {
		sendMessage(user.fd, std::string(ERR_CHANOPRIVSNEEDED(user.nick, chan->first)) + "\n", std::cerr);
		return;
	}
	if (args.size() == 2) {
		if (chan->second.getTopic().empty()) {
			sendMessage(user.fd, NOTOPIC(user.nick, chan->second.getName()) + "\n", std::cout);
		} else {
			sendMessage(user.fd, TOPIC(user.nick, chan->second.getName()) + chan->second.getTopic() + "\n", std::cout);
		}
		return;
	}
	std::string mess;
	for (size_t i = 2; i < args.size(); i++) {
		if (i == 2) {
			args[i].erase(0,1);
			mess = args[i];
		}
		else
			mess += " " + args[i];
	}
	chan->second.setTopic(mess);

	std::vector<int> users = chan->second.getUsers();
	for (std::vector<int>::iterator it = users.begin(); it != users.end(); it++)
		sendMessage(srv._users[*it].fd, TOPIC(srv._users[*it].nick, chan->second.getName()) + chan->second.getTopic() + "\n", std::cout);
}
