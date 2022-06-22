//Définit le mot de passe avant toute tentative de connexion
//PASS <mot de passe>

#include "../../includes/SockServer.hpp"

void SockServer::pass(SockServer& srv, std::vector<std::string> args, User& user) {
	std::cout << "Commande PASS -> " << srv.password << std::endl; //debug
	std::cout << "-" << args[1] << "-" << std::endl;
	if (args.size() != 2 || args[0] != "PASS")
		return ;
	if (args[1] == srv.password)
		user.pass = 1;
	else {
		user.pass = 0;
		srv.transmit(user, "Pass is good", std::cout);
	}
}

//TODO -> ERRORS
