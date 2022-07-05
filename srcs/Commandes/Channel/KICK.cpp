// Commande: KICK
// Paramètres: <canal> <utilisateur> [<commentaire>]

// La commande KICK est utilisée pour retirer par la force un utilisateur d'un canal (PART forcé).

// Seul un opérateur de canal peut kicker un autre utilisateur hors d'un canal. 
// Tout serveur qui reçoit un message KICK vérifie si le message est valide 
// (c'est-à-dire si l'expéditeur est bien un opérateur du canal) avant d'ôter la victime du canal.

// Réponses numériques :

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
//            ERR_NOTONCHANNEL
// Exemples:

// KICK &Melbourne Matthew ; Kick Matthew de &Melbourne
// KICK #Finnish John :Speaking English ; Kick John de #Finnish en spécifiant "Speaking English" comme raison (commentaire).
// :WiZ KICK #Finnish John ; Message KICK de WiZ pour retirer John du canal #Finnish

#include "../../includes/SockServer.hpp"

void SockServer::kick(SockServer &srv, std::vector<std::string>& args, User& user)
{
	//TODO Verifier les arguments. Si plusieurs channels : obligatoirement le meme nombre de users. Si Un channel, possiblite d'avoir plusieurs users pour le meme channel
	if (args.size() < 3 && args[0] != "KICK")
		return ;
	if (!cInSet(args[1][0], "#&+!")) { //Le deuxième argument n'est pas un channel
		std::cerr << "Not a channel";
		return ;
	}
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]); //Le channel n'existe pas
	if (chan == srv._chans.end()) {
		sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
		return;
	}
	if (!user.channels.count(&chan->second)) { //L'envoyeur n'est pas dans le channel
		std::cerr << "Not in channel" << std::endl;
		return ;
	}
	if (chan->second.isOper(user.fd) == false) { //L'envoyeur n'est pas opérateur
		std::cerr << "Error: Don't have this privilege" << std::endl;
		return ;
	}
	User *u_kick = srv.getUserByNick(args[2]);
	if (u_kick == NULL) { //La cible n'existe pas
		std::cerr << "Target doesn't exist" << std::endl;
		return ;
	}
	if (!u_kick->channels.count(&chan->second)) { //La cible n'est pas dans le channel
		std::cerr << "Target is not in the channel" << std::endl;
		return ;
	}

	std::string mess = "Was kicked. Reason";
	if (args[3] != ":")
		for (size_t i = 3; i < args.size(); i++) {
			if (i == 3) {
				mess += ": ";
				args[i].erase(0,1);
			}
			mess += " " + args[i];
		}
	if (mess == "Was kicked. Reason")
		mess += " not provided";
	mess += "\n";

	transmitToChannelFromServ(chan->second, PART(u_kick->nick, u_kick->user, chan->second.getName()) + mess);

	int fd_op = u_kick->leaveChannel(&chan->second);
	if (fd_op != -1) {
		srv._users[fd_op].channels[&chan->second] = true;
		std::cout << srv._users[fd_op].nick + " is now op on the channel " + chan->second.getName() << std::endl;
	}
	if (chan->second.isEmpty())
		srv._chans.erase(chan->second.getName());
}
