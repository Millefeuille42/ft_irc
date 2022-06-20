//Définit le pseudonyme d'un utilisateur
//NICK <pseudonyme>

#include "../commands.hpp"

void u_nick(SockServer& srv, std::vector<std::string> args, User& user) {
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
}