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
	std::string tokickuser = args[2];
	std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);

	if (args.size() < 2)
	{
		std::cerr << "Error: Need param" << std::endl;
 		return ;
	}
	if (chan == srv._chans.end()) {
 		std::cerr << "No such channel {" + args[1] + "}" << std::endl;
		return;
	}
	else if (!srv.getUserByNick(tokickuser) || !srv.getUserByRealName(tokickuser) || !srv.getUserByUsername(tokickuser))
	{
		std::cerr << "Error: Unknown user" << std::endl;
		return ;
	}
	// else if (chan existe mais pas le mec dedans)
	// {
	// 	std::cerr << "Error: User isn't in this Channel" << std::endl;
	// }
	else if (chan->second.isOper(user.fd) == false)
	{
		std::cerr << "Error: Don't have this privilege" << std::endl;
	}
	else 
	{
		// on kick le batard

	}
}
