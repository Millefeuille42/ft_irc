//Envoyer un message privé à un/des utilisateur.
//PRIVMSG <destinataire>{,<destinataire>} <texte à envoyer >

//Si channel en Mode n -> Verifier si le user est bien dedans. Sinon impossible d'envoyer.
//Verifier si l'utilisateur est ban du channel.

#include "../../includes/SockServer.hpp"

// PRIVMSG #cheval :prout
// PRIVMSG millefeuille :hello hru
void SockServer::privmsg(SockServer &srv, std::vector<std::string> &args, User &user) {
	if (args.size() < 3) {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick)) + "\n", std::cout);
		return;
	}

	if (*args[2].begin() != ':') { //Le message doit commencer par : et peut contenir des espaces
		sendMessage(user.fd, std::string(ERR_NOTEXTTOSEND(user.nick)) + "\n", std::cout);
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
			sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
			return;
		}
		if (chan->second.isMode('n') && !user.channels.count(&chan->second)) {
			sendMessage(user.fd, std::string(ERR_NOTONCHANNEL(user.nick, chan->first)) + "\n", std::cout);
			return;
		}
		transmitToChannel(chan->second, user, PRIVMSG(user.nick, user.user, args[1]) + message + "\n");
	} else {
		User *target = srv.getUserByNick(args[1]);
		if (!target) {
			sendMessage(user.fd, std::string(ERR_NOSUCHNICK(user.nick, args[1])) + "\n", std::cout);
			return;
		}
		sendMessage(target->fd, PRIVMSG(user.nick, user.user, target->nick) + message + "\n", std::cout);
	}
}
