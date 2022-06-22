//Sert à spécifier le nom d'utilisateur, et le vrai nom de l'utilisateur.
//USER <nom d'utilisateur> <hôte> <nom de serveur> <nom réel>
//Ignorer Hote et Nom de serveur

#include "../../includes/SockServer.hpp"

void SockServer::user(SockServer& srv, std::vector<std::string> args, User& user) {
	std::cout << "Commande USER" << std::endl; //debug
	(void)srv;
	if (args[0] != "USER" || args.size() < 5)
		return ;
	user.user = args[1];
	if (*args[4].begin() == ':') //Le nom réel doit commencer par : et peut contenir des espaces
		user.realName = args[4];
	else
		return ;
	for (size_t i = 5; i < args.size(); i++) {
		user.realName += " " + args[i];
	}
	srv.transmit(user, "Name is set\n", std::cout);
}
