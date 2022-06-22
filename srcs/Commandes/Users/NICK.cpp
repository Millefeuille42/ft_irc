//Définit le pseudonyme d'un utilisateur
//NICK <pseudonyme>

#include "../../includes/SockServer.hpp"

void SockServer::nick(SockServer& srv, std::vector<std::string> args, User& user) {
	std::cout << "Commande NICK" << std::endl; //debug
	if (args.size() != 2 || args[0] != "NICK")
		return ;
	stringVector::iterator itu;
	for (stringVector::iterator it = srv.getNicks().begin(); it != srv.getNicks().end(); it++) {
		if (user.nick == *it)
			itu = it;
		if (args[1] == *it)
			return ; //Le Nick existe déjà sur le serveur
	}
	user.nick = args[1];
	srv.getNicks().erase(itu);
	srv.getNicks().push_back(args[1]);
	srv.transmit(user, "Nick is set", std::cout);
}
