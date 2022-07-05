//Obtenir les privilèges opérateurs
//OPER <utilisateur> <mot de passe>

#include "../../includes/SockServer.hpp"

void SockServer::oper(SockServer &, std::vector<std::string>& args, User& user) {
	if (args.size() != 3 || args[0] != "OPER") {
		if (user.nick.empty())
			sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS_NONICK) + "\n", std::cout);
		else
			sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick)) + "\n", std::cout);
		return;
	}
	if (args[1] == "admin" && args[2] == "safepass42") {
		user.modes['o'] = true;
		sendMessage(user.fd, YOUREOPER(user.nick) + "\n", std::cout);
	}
	else
		sendMessage(user.fd, ERR_PASSWDMISMATCH(user.nick) + "\n", std::cout);
}
