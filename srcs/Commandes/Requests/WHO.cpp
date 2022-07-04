//Envoyer les liste d'informations des utilisateurs.
//WHO [<nom> [<o>]]


// La commande /who te permet d'afficher des informations sur les utilisateurs. 
// Sans argument, cela retourne la liste des personnes connectées sur le réseau. 
// Tu peux néanmoins spécifier un channel ou un mask pour nickname, usernamer ou hostname. 
// Enfin, tu peux lister les IRCOperators en spécifiant o en deuxième argument.

// /who [channel | mask] [o]

// The WHO command is used by a client to generate a query which returns
// a list of information which 'matches' the <mask> parameter given by
// the client.  In the absence of the <mask> parameter, all visible
// (users who aren't invisible (user mode +i) and who don't have a
// common channel with the requesting client) are listed.  The same
// result can be achieved by using a <mask> of "0" or any wildcard which
// will end up matching every visible user.

// The <mask> passed to WHO is matched against users' host, server, real
// name and nickname if the channel <mask> cannot be found.

// If the "o" parameter is passed only operators are returned according
// to the <mask> supplied.

// Numeric Replies:

// ERR_NOSUCHSERVER
// RPL_WHOREPLY			RPL_ENDOFWHO

// Examples:

// WHO *.fi            ; Command to list all users who match against "*.fi".

// WHO jto* o          ; Command to list all users with a match against "jto*" if they are an operator.

#include "../../includes/SockServer.hpp"
#include <cstddef>

void SockServer::who(SockServer &srv, std::vector<std::string> & args, User& user)
{
	if (args.size() < 2)
	{
		// std::cout << "Informations on all connected users :" << std::endl;
		srv.sendMessage(1, "Informations on all connected users :\n");
		for (size_t i = 1; i < srv._fds.size(); i++)
		{
			// std::cout << "IP Adress\t\t: " << user.ip << "\nUser Name\t\t: " << user.user << "\nReal Name\t\t: " << user.realName << "\nNick Name\t\t: " << user.nick << std::endl;
			// srv.sendMessage(1, "IP Adress :" + srv._users + "\n");
			// srv.sendMessage(1, "User Name :" + user[i].user + "\n");
			// srv.sendMessage(1, "Real Name :" + user[i].realName + "\n");
			srv.sendMessage(1, "Nick Name :" + srv._users[srv._fds[i], NULL].nick + "\n");
		}
	}
	else if (args[1] == "o")
	{
		// en theorie ici faut mettre les user qui sont dans le serveur et operateur
	}
	else if (!srv._chans.count(args[1]))
	{
		// en theorie ici faut mettre les user qui sont dans le channels precise en args
	}
	// else if (!srv.getUserByNick(args[1]) || !srv.getUserByRealName(args[1]) || !srv.getUserByUsername(args[1]))
	// {
	// 	sendMessage(2, "Error: Unknown user");
	// }
	else if (args[1] == user.user || args[1] == user.realName || args[1] == user.nick)
	{
		// if (args[2] == "o")
		// {
			// afficher que les irc operators qui contiennent des infos de larg 1
		// }
		// else 
		// {
		srv.sendMessage(1, "Informations on the request user :\n", std::cout);
		srv.sendMessage(1, "IP Adress :" + user.ip + "\n", std::cout);
		srv.sendMessage(1, "User Name :" + user.user + "\n", std::cout);
		srv.sendMessage(1, "Real Name :" + user.realName + "\n", std::cout);
		srv.sendMessage(1, "Nick Name :" + user.nick + "\n\n", std::cout);
		// std::cout << "Informations on the request user :" << std::endl;
		// std::cout << "IP Adress\t\t: " << user.ip << std::endl;
		// std::cout << "User\t\t: " << user.user << std::endl;
		// std::cout << "Real Name\t\t: " << user.realName << std::endl;
		// std::cout << "Nick\t\t: " << user.nick << std::endl;
		// }
	}
	// else
	// {

	// }

}