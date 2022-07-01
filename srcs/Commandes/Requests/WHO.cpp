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

// #include "../../includes/SockServer.hpp"

// void SockServer::who(SockServer &srv, std::vector<std::string> & args, User& user)
// {
// 	if (args.size() < 1)
// 	{
// 		for (int i = 0; i < user.fd; i++)
// 			srv.sendMessage(user.fd, "have been killed\n", std::cout);
// 	}

// 	else if (!srv._chans.count(args[1]))
// 	{

// 	}

// 	else if (args == user.user || args == user.realName || args == user.nick)
// 	{
// 		std::cout << "Informations on the request user :" << std::endl;
// 		std::cout << "IP Adress\t\t: " << user.ip << std::endl;
// 		std::cout << "User\t\t: " << user.user << std::endl;
// 		std::cout << "Real Name\t\t: " << user.realName << std::endl;
// 		std::cout << "Nick\t\t: " << user.nick << std::endl;
// 	}

// 	else if (args == "o")
// 	{

// 	}

// 	else
// 	{

// 	}

// }