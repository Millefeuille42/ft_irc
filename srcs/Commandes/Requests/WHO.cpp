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

void SockServer::who(SockServer &srv, std::vector<std::string> & args, User&)
{
	if ((cInSet(args[1][0], "#&+!") && args.size() < 3) || (args.size() < 3 && args[1] == "0"))
	{
		std::cout << "List of all connected users :" << std::endl;
		for (size_t i = 1; i < srv._fds.size(); i++)
			std::cout << "\t- Utilisateur " << i << " : " << srv._users[srv._fds[i].fd].realName << " -" << std::endl;
		std::cout << "End of the list." << std::endl;
	}
	else if (!srv.getUserByNick(args[1]) && !srv.getUserByRealName(args[1]) && !srv.getUserByUsername(args[1]))
	{
		std::cerr << "Error: Unknown user" << std::endl;
	}
	else if ((args.size() < 3 && args[1] != "0") || (args.size() < 4 && args[2] == "o" && args[1] != "0"))
	{
		if (args[2] == "o")
		{
			for (size_t i = 1; i < srv._fds.size(); i++)
			{
				if (srv._users[srv._fds[i].fd].modes['o'] == true)
				{
					std::cout << "Informations on the request user :" << std::endl;
					std::cout << "\t- Operateur " << srv._users[srv._fds[i].fd].user << " -" << std::endl;
					std::cout << "\t   - " << srv._users[srv._fds[i].fd].ip << std::endl;
					std::cout << "\t   - " << srv._users[srv._fds[i].fd].user << std::endl;
					std::cout << "\t   - " << srv._users[srv._fds[i].fd].realName << std::endl;
					std::cout << "\t   - " << srv._users[srv._fds[i].fd].nick << std::endl;
				}
			}
		}
		else
		{
			for (size_t i = 1; i < srv._fds.size(); i++)
			{
				std::cout << "Informations on the request user :" << std::endl;
				std::cout << "\t- Utilisateur " << srv._users[srv._fds[i].fd].user << " -" << std::endl;
				std::cout << "\t   - " << srv._users[srv._fds[i].fd].ip << std::endl;
				std::cout << "\t   - " << srv._users[srv._fds[i].fd].user << std::endl;
				std::cout << "\t   - " << srv._users[srv._fds[i].fd].realName << std::endl;
				std::cout << "\t   - " << srv._users[srv._fds[i].fd].nick << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Informations on all connected users :" << std::endl;
		for (size_t i = 1; i < srv._fds.size(); i++)
		{
			std::cout << "\t- Utilisateur " << srv._users[srv._fds[i].fd].user << " -" << std::endl;
			std::cout << "\t   - " << srv._users[srv._fds[i].fd].ip << "" << std::endl;
			std::cout << "\t   - " << srv._users[srv._fds[i].fd].user << "" << std::endl;
			std::cout << "\t   - " << srv._users[srv._fds[i].fd].realName << "" << std::endl;
			std::cout << "\t   - " << srv._users[srv._fds[i].fd].nick << "" << std::endl;
		}
		std::cout << "End of the list." << std::endl;
	}
	return ;
}
