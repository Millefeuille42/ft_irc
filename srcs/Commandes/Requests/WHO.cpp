// Commande: WHO
// Paramètres: [<nom> [<o>]]

// Le message WHO est utilisé par un client pour générer une requête qui renvoie une liste d'informations
// qui correspondent au paramètre <nom> donné par le client. Si le paramètre nom est absent, 
// tous les utilisateurs visibles (ceux qui ne sont pas invisibles (mode utilisateur +i) et qui n'ont 
// pas de canal en commun avec le client émettant la requête) sont listés. 
// Le même résultat peut être obtenu en utilisant le <nom> "0" ou tout joker correspondant à toutes les entrées possibles.

// Le <nom> passé en paramètre est mis en correspondance avec les hôtes des utilisateurs, 
// leurs véritables noms, et leurs pseudonymes si le canal <nom> n'est pas trouvé.

// Si le paramètre "o" est passé, seuls les opérateurs sont listés, et ce, en fonction du masque fourni.

// Réponses numériques :

//            ERR_NOSUCHSERVER
//            RPL_WHOREPLY                    RPL_ENDOFWHO

#include "../../includes/SockServer.hpp"

typedef std::vector<User *>(*listFunc)(SockServer &, const std::string &);

static void sendMessageByUserMatch(SockServer &srv, const User& sender, listFunc fc, const std::string& arg, const std::string& match) {
	std::vector<User *> userList = fc(srv, arg);
	if (userList.empty())
		return;
	SockServer::sendMessage(sender.fd, "WHO matches by " + match + "\n", std::cout);
	for (std::vector<User *>::iterator uit = userList.begin(); uit != userList.end(); uit++) {
		if (*uit == NULL)
			continue ;
		SockServer::sendMessage(sender.fd, WHOREPLY(sender.nick, "*", (*uit)->user, (*uit)->nick, "", (*uit)->realName) + "\n", std::cout);
	}
	SockServer::sendMessage(sender.fd, ENDOFWHO(sender.nick, arg, match) + "\n", std::cout);
}

void SockServer::who(SockServer &srv, std::vector<std::string> & args, User& user) {
	// Si y a rien ou 0 (tout lister)
	if (args.size() < 2 || (args.size() < 3 && args[1] == "0"))
	{
		SockServer::sendMessage(user.fd, "WHO matches by global\n", std::cout);
		// QUAND Global pas de @
		// :fiery.ca.us.SwiftIRC.net 352 fess * ~caca CE7E5A6D.36C1EBC7.DF0F43E2.IP * fess H :0 danles fess
		for (fdIterator fd = srv._fds.begin(); fd != srv._fds.end(); fd++) {
			User &dude = srv._users[fd->fd];
			if (fd == srv._fds.begin())
				continue;
			SockServer::sendMessage(user.fd, WHOREPLY(user.nick, "*", dude.user, dude.nick, "", dude.realName) + "\n", std::cout);
		}
		SockServer::sendMessage(user.fd, ENDOFWHO(user.nick, args[1], "global") + "\n", std::cout);
		std::cout << "End of the list." << std::endl;
	} else {
		// QUAND User non plus
		// :fiery.ca.us.SwiftIRC.net 352 fess * ~caca CE7E5A6D.36C1EBC7.DF0F43E2.IP * fess H :0 danles fess
		sendMessageByUserMatch(srv, user, getUsersByNick, args[1], "nick");
		sendMessageByUserMatch(srv, user, getUsersByUsername, args[1], "username");
		sendMessageByUserMatch(srv, user, getUsersByRealName, args[1], "realname");

		// QUAND Channel, @ = operator channel
		// :fiery.ca.us.SwiftIRC.net 352 fess #monzizienorme ~caca CE7E5A6D.36C1EBC7.DF0F43E2.IP * fess H@ :0 danles fess
		bool operatorMode = false;
		if (args.size() > 1 && *(args.end() - 1) == "o")
			operatorMode = true;
		bool hasMatch = false;
		for (channelsMap::iterator chan = srv._chans.begin(); chan != srv._chans.end(); chan++) {
			if (chan->first != args[1])
				continue;
			if (!hasMatch) {
				hasMatch = true;
				SockServer::sendMessage(user.fd, "WHO matches by channel\n", std::cout);
			}
			std::vector<int> userList = chan->second.getUsers();
			for (std::vector<int>::iterator userFd = userList.begin(); userFd != userList.end(); userFd++) {
				User &dude = srv._users[*userFd];
				if (chan->second.isOper(*userFd))
					SockServer::sendMessage(user.fd, WHOREPLY(user.nick, chan->first, dude.user, dude.nick, "@", dude.realName) + "\n", std::cout);
				else if (!operatorMode)
					SockServer::sendMessage(user.fd, WHOREPLY(user.nick, chan->first, dude.user, dude.nick, "", dude.realName) + "\n", std::cout);
			}
		}
		if (hasMatch)
			SockServer::sendMessage(user.fd, ENDOFWHO(user.nick, args[1], "by channel") + "\n", std::cout);
	}
}
