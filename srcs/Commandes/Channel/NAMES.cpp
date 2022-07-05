// Commande: NAMES
// Paramètres: [<canal>{,<canal>}]

// En utilisant la commande NAMES, un utilisateur peut obtenir la liste des pseudonymes 
// visibles sur n'importe quel canal qu'il peut voir. Les noms de canaux qu'il peut voir 
// sont ceux qui ne sont ni privés (+p), ni secrets (+s), ou ceux sur lesquels il est 
// actuellement. Le paramètre <canal> spécifie quels sont les canaux dont l'information 
// est voulue, s'ils sont valides. Il n'y a pas de message d'erreur pour les noms de canaux invalides.

// Si le paramètre <canal> n'est pas donné, la liste de tous les canaux et de leurs 
// occupants est renvoyée. A la fin de cette liste, sont listés les utilisateurs visibles, 
// mais qui n'appartiennent à aucun canal visible. Ils sont listés comme appartenant au 'canal' "*".

// Réponses numériques:

//            RPL_NAMREPLY                    RPL_ENDOFNAMES

// Exemples:

//     NAMES #twilight_zone,#42 ; liste les utilisateurs visibles sur #twilight_zone et #42, si ces canaux vous sont visibles.
//     NAMES ; liste tous les canaux, et tous les utilisateurs visibles. 

#include "../../includes/SockServer.hpp"


std::vector<std::string> parseMess(std::string msg)
{
	std::vector<std::string> args;
	size_t pos;
	std::string token;
	while ((pos = msg.find(',')) != std::string::npos)
    {
		token = msg.substr(1, pos);
		args.push_back(token);
		msg.erase(0, pos + 1);
	}
	args.push_back(msg);
	return args;
}

void SockServer::names(SockServer &srv, std::vector<std::string> & args, User&)
{
    if (!cInSet(args[1][0], "#&+!") && args.size() < 3) // en gros la c'est y a rien qui est dit donc on liste tous les chan et les gens dedans 1 par 1, et le dernier chan c'est la liste des gens qui sont nulpart et le chan s'apellerio (pas quezac) '*'
    {
        for (channelsMap::iterator it = srv._chans.begin(); it != srv._chans.end(); it++)
        {
            std::cout << it->first << std::endl;
            std::vector<int> user_list = it->second.getUsers();
            for (std::vector<int>::iterator it2 = user_list.begin(); it2 != user_list.end(); it2++)
            {
                std::cout << "\t- Utilisateur " << *it2 << " : " << srv._users[srv._fds[*it2].fd].nick << " -" << std::endl;
            }
        } // manque le chan * avec les recalcitrants
    }
    else // et la j'essaie de recuperer les channels qui ont ete envoye, separe par juste une virgule si il y en a + d'1, et ecrit avec un # devant
    {
        std::vector<std::string> chan_list = parseMess(args[1]);
        for (std::vector<std::string>::iterator i = chan_list.begin(); i != chan_list.end(); i++)
        {
            std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(*i);
            if (chan == srv._chans.end())
		        return ;
            std::cout << *i << std::endl;
            std::vector<int> user_list = chan->second.getUsers();
            for (std::vector<int>::iterator it2 = user_list.begin(); it2 != user_list.end(); it2++)
            {
                std::cout << "\t- Utilisateur " << *it2 << " : " << srv._users[srv._fds[*it2].fd].nick << " -" << std::endl;
            }
        }
    }
} // TODO -> faire le truc comme topic, parce que irssi il fait chier la
