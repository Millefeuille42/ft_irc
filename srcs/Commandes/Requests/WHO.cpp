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
// Exemples:

// WHO *.fi ; Liste tous les utilisateurs qui correspondent à "*.fi".
// WHO jto* o ; Liste tous les utilisateurs qui correspondent à "jto*", s'ils sont opérateurs.

#include "../../includes/SockServer.hpp"
#include <cstddef>

void SockServer::who(SockServer &srv, std::vector<std::string> & args, User&)
{
	if (args.size() < 3 || (args.size() < 4 && args[3] == "0"))
	{
		std::cout << "List of all connected users :" << std::endl;
		for (size_t i = 1; i < srv._fds.size(); i++)
			std::cout << "\t- Utilisateur " << i << " : " << srv._users[srv._fds[i].fd].realName << " -" << std::endl;
		std::cout << "End of the list." << std::endl;
	}
	// else if (args.size() == 3 && args[2] == "o")
	// {
	// 	// en theorie ici faut mettre les user qui sont dans le serveur et operateur
	// }
	// else if (!srv.getUserByNick(args[1]) || !srv.getUserByRealName(args[1]) || !srv.getUserByUsername(args[1]))
	// {
	// 	sendMessage(2, "Error: Unknown user");
	// }
	else if (args.size() < 4 && args[3] != "0")
	{
		// int size_args = args[2].size();
		// if (args[2][0] == '*')
		// {
		// 	args[2].find_last_of(args[2], 1);
		// }
		// // if (args.size() == 5 && args[5] == "o")
		// // {
		// 	// afficher que les irc operators qui contiennent des infos de larg 1
		// // }
		// if (args[2][size_args] == '*')
		// {
		// 	for (size_t i = 1; i < srv._fds.size(); i++)
		// 	{
		// 		for (int j = 0; j < args[i][size_args - 1]; j++)
		// 		{
		// 			if (args[i][j] != srv._users[srv._fds[i].fd][j])
		// 		}
		// 	}
		// }
		// else
		// {
			for (size_t i = 1; i < srv._fds.size(); i++)
			{
				std::cout << "Informations on the request user :" << std::endl;
				std::cout << "\t- Utilisateur " << srv._users[srv._fds[i].fd].user << " -" << std::endl;
				std::cout << "\t\t- " << srv._users[srv._fds[i].fd].ip << "" << std::endl;
				std::cout << "\t\t- " << srv._users[srv._fds[i].fd].user << "" << std::endl;
				std::cout << "\t\t- " << srv._users[srv._fds[i].fd].realName << "" << std::endl;
				std::cout << "\t\t- " << srv._users[srv._fds[i].fd].nick << "" << std::endl;
			}
		// }
	}
	else 
	{
		std::cout << "Informations on all connected users :" << std::endl;
		for (size_t i = 1; i < srv._fds.size(); i++)
		{
			std::cout << "\t- Utilisateur " << srv._users[srv._fds[i].fd].user << " -" << std::endl;
			std::cout << "\t\t- " << srv._users[srv._fds[i].fd].ip << "" << std::endl;
			std::cout << "\t\t- " << srv._users[srv._fds[i].fd].user << "" << std::endl;
			std::cout << "\t\t- " << srv._users[srv._fds[i].fd].realName << "" << std::endl;
			std::cout << "\t\t- " << srv._users[srv._fds[i].fd].nick << "" << std::endl;
		}
		std::cout << "End of the list." << std::endl;
	}

}
