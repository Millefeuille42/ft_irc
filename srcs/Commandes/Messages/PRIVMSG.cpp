//Envoyer un message privé à un/des utilisateur.
//PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer >

//Si channel en Mode n -> Verifier si le user est bien dedans. Sinon impossible d'envoyer.
//Verifier si l'utilisateur est ban du channel.

#include "../../includes/SockServer.hpp"

// PRIVMSG #cheval :prout
// PRIVMSG millefeuille :hello hru
void SockServer::privmsg(SockServer &srv, std::vector<std::string> &args, User &user) {
	if (args.size() < 3)
		return ;

	if (*args[2].begin() != ':') { //Le message doit commencer par : et peut contenir des espaces
		std::cerr << "Missing :" << std::endl;
		return;
	}
	args[2].erase(0,1);
	std::string message = args[2];
	for (size_t i = 3; i < args.size(); i++) {
		message += " " + args[i];
	}

	if (cInSet(args[1][0], "#&+!")) {
		std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);
		if (chan == srv._chans.end()) {
			std::cerr << "No such channel {" + args[1] + "}" << std::endl;
			return;
		}
		if (chan->second.isMode('n') && !user.channels.count(&chan->second)) {
			std::cerr << "Not in channel" << std::endl;
			return;
		}
		transmitToChannel(chan->second, user, PRIVMSG(user.nick, user.user, args[1]) + message + "\n");
	} else {
		User *target = srv.getUserByNick(args[1]);
		if (!target) {
			std::cerr << "No such user" << std::endl;
			return;
		}
		sendMessage(target->fd, PRIVMSG(user.nick, user.user, target->nick) + message + "\n", std::cout);
	}
}
