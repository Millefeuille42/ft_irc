//Modifier ou voir le sujet d'un canal
//TOPIC <canal> [<sujet>]

#include "../../includes/SockServer.hpp"

void SockServer::topic(SockServer &srv, std::vector<std::string> &args, User &user) {
	if (args.size() < 2 && args[0] != "topic")
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
	if (chan->second.isMode('t') && chan->second.isOper(user.fd) == false) {
		std::cerr << "Not an operator and mode \'t\' is on" << std::endl;
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

	//TODO Je suppose qu'il faut envoyer le topic à IRSSI mais jsp comment :)
}
