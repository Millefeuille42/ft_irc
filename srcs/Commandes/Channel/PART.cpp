//Quitter un channel
//PART <canal>{,< canal >}

#include "../../includes/SockServer.hpp"

void SockServer::part(SockServer &srv, std::vector<std::string> &args, User& user) {
	if (args.size() < 2 && args[0] != "PART")
		return ;
	if (!cInSet(args[1][0], "#&+!")) {
		std::cerr << "Not a channel";
		return ;
	}
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);
	if (chan == srv._chans.end()) {
		std::cerr << "No such channel {" + args[1] + "}" << std::endl;
		return;
	}
	if (chan->second.isMode('n') && !user.channels.count(&chan->second)) {
		std::cerr << "Not in channel" << std::endl;
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
	user.leaveChannel(&chan->second);
}
