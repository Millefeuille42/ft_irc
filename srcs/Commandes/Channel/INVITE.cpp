//Inviter un utilisateur dans un canal.
//INVITE <pseudonyme> <canal>

#include "../../includes/SockServer.hpp"

void SockServer::invite(SockServer &srv, std::vector<std::string> &args, User& user) {
	if (args[0] != "INVITE" || args.size() <= 2)
		return ;

	//Parser les users séparés par une virgule args[2]

	if (!cInSet(args[2][0], "#&+!")) { //Le deuxième argument n'est pas un channel
		std::cerr << "Not a channel";
		return ;
	}
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[2]); //Le channel n'existe pas
	if (chan == srv._chans.end()) {
		sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
		return;
	}
	if (!user.channels.count(&chan->second)) { //L'envoyeur n'est pas dans le channel
		std::cerr << "Not in channel" << std::endl;
		return ;
	}
	if (chan->second.isOper(user.fd) == false && chan->second.isMode('i') == true) { //L'envoyeur n'est pas opérateur et le mode 'i' est actif
		std::cerr << "Error: Don't have this privilege" << std::endl;
		return ;
	}

	//TODO boucle à partir d'ici pour ajouter plusieurs users {
		User *u_invit = srv.getUserByNick(args[1]);
		if (u_invit == NULL) { //La cible n'existe pas
			std::cerr << "Target doesn't exist" << std::endl;
			return ;
		}
		if (u_invit->channels.count(&chan->second)) { //La cible est deja dans le channel
			std::cerr << "Target is already in the channel" << std::endl;
			return ;
		}
		chan->second.joinChannel(u_invit->fd); //Channel rejoins
		u_invit->enterChannel(&chan->second, false);
		transmitToChannelFromServ(chan->second, JOIN(u_invit->nick, u_invit->user, chan->first) + "\n");
		if (!chan->second.getTopic().empty()) {
			sendMessage(u_invit->fd, TOPIC(u_invit->nick, chan->second.getName()) + chan->second.getTopic() + "\n", std::cout);
		}
	//}
}
