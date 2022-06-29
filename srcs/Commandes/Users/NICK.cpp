//Définit le pseudonyme d'un utilisateur
//NICK <pseudonyme>

#include "../../includes/SockServer.hpp"

void SockServer::nick(SockServer& srv, std::vector<std::string>& args, User& user) {
	std::cout << "Commande NICK" << std::endl; //debug
	if (args.size() != 2 || args[0] != "NICK")
		return ;
	std::string oldNick;
	stringVector::iterator itu = srv.getNicks().end();
	for (stringVector::iterator it = srv.getNicks().begin(); it != srv.getNicks().end(); it++) {
		if (user.nick == *it) {
			itu = it;
			oldNick = user.nick;
		}
		if (args[1] == *it)
			return ; //Le Nick existe déjà sur le serveur
	}
	user.nick = args[1];
	if (itu != srv.getNicks().end()) {
		std::string mess = oldNick + " rename in " + user.nick + "\n";
		srv.transmitServ(mess);
		srv.getNicks().erase(itu);
	}
	else
		welcome(srv, args, user);
	srv.getNicks().push_back(args[1]);
	std::cout << "Nick is set" << std::endl;
}
