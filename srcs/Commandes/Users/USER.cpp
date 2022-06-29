//Sert à spécifier le nom d'utilisateur, et le vrai nom de l'utilisateur.
//USER <nom d'utilisateur> <mode> <nom de serveur> <nom réel>
//Ignorer Hote et Nom de serveur

#include "../../includes/SockServer.hpp"

void SockServer::user(SockServer &srv, std::vector<std::string>& args, User& user) {
	std::cout << "Commande USER" << std::endl; //debug
	if (args[0] != "USER" || args.size() < 5)
		return ;
	if (*args[4].begin() == ':') { //Le nom réel doit commencer par : et peut contenir des espaces
		user.user = args[1];
		args[4].erase(0,1);
		user.realName = args[4];
	}
	else
		return ;
	for (size_t i = 5; i < args.size(); i++) {
		user.realName += " " + args[i];
	}
	std::cout << "Name is set" << std::endl;
	welcome(srv, args, user);
}
