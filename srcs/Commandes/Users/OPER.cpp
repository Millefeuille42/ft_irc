//Obtenir les privilèges opérateurs
//OPER <utilisateur> <mot de passe>

#include "../../includes/SockServer.hpp"

void SockServer::oper(SockServer &srv, std::vector<std::string>& args, User& user) {
	if (args.size() != 3 || args[0] != "OPER")
		return ;
	if (args[1] == "admin" && args[2] == "safepass42") {
		user.modes["o"] = true;
		srv.sendMessage(user.fd, user.nick + ", You are now an Operator !\n", std::cout);
	}
	else
		srv.sendMessage(user.fd, "Bad combinaison to be an operator.\n", std::cout);
}
