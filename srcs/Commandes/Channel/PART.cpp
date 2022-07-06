//Quitter un channel
//PART <canal>{,< canal >}

#include "../../includes/SockServer.hpp"

void SockServer::part(SockServer &srv, std::vector<std::string> &args, User& user) {
	// TODO On peut quitter plusieurs channels d'un coup, meme syntaxe que join
	if (args.size() < 2 && args[0] != "PART") {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick, args[0])) + "\n", std::cout);
		return;
	}
	if (!cInSet(args[1][0], "#&+!")) {
		std::cerr << "Not a channel";
		return ;
	}
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);
	if (chan == srv._chans.end()) {
		sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
		return;
	}
	if (!user.channels.count(&chan->second)) {
		sendMessage(user.fd, std::string(ERR_NOTONCHANNEL(user.nick, chan->first)) + "\n", std::cout);
		return;
	}
	std::string mess = "Reason";
	for (size_t i = 2; i < args.size(); i++) {
		if (i == 2) {
			mess += ": ";
			args[i].erase(0,1);
		}
		mess += " " + args[i];
	}
	if (mess == "Reason")
		mess += " not provided";
	mess += "\n";
	transmitToChannelFromServ(chan->second, PART(user.nick, user.user, chan->second.getName()) + mess);
	int fd_op = user.leaveChannel(&chan->second);
	if (fd_op != -1) {
		srv._users[fd_op].channels[&chan->second] = true;
		transmitToChannelFromServ(chan->second, CHANOPER(chan->first, srv._users[fd_op].nick));
	}
	if (chan->second.isEmpty())
		srv._chans.erase(chan->second.getName());
}
