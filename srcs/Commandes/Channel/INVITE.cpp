//Inviter un utilisateur dans un canal.
//INVITE <pseudonyme> <canal>

#include "../../includes/SockServer.hpp"

void SockServer::invite(SockServer &srv, std::vector<std::string> &args, User& user) {
	if (args[0] != "INVITE" || args.size() <= 2) {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick)) + "\n", std::cout);
		return;
	}

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
		sendMessage(user.fd, std::string(ERR_NOTONCHANNEL(user.nick, chan->first)) + "\n", std::cout);
		return;
	}
	if (chan->second.isOper(user.fd) == false && chan->second.isMode('i') == true) { //L'envoyeur n'est pas opérateur et le mode 'i' est actif
		sendMessage(user.fd, std::string(ERR_CHANOPRIVSNEEDED(user.nick, chan->first)) + "\n", std::cout);
		return;
	}

	User *u_invit = srv.getUserByNick(args[1]);
	if (u_invit == NULL) { //La cible n'existe pas
		sendMessage(user.fd, std::string(ERR_NOSUCHNICK(user.nick, args[1])) + "\n", std::cout);
		return;
	}
	if (u_invit->channels.count(&chan->second)) { //La cible est deja dans le channel
		sendMessage(user.fd, std::string(ERR_USERONCHANNEL(user.nick, u_invit->nick , chan->first)) + "\n", std::cout);
		return;
	}
	chan->second.joinChannel(u_invit->fd); //Channel rejoins
	u_invit->enterChannel(&chan->second, false);
	transmitToChannelFromServ(chan->second, JOIN(u_invit->nick, u_invit->user, chan->first) + "\n");
	if (!chan->second.getTopic().empty()) {
		sendMessage(u_invit->fd, TOPIC(u_invit->nick, chan->second.getName()) + chan->second.getTopic() + "\n", std::cout);
	}
}
