//Sert à spécifier le nom d'utilisateur, et le vrai nom de l'utilisateur.
//USER <nom d'utilisateur> <hôte> <nom de serveur> <nom réel>
//Ignorer Hote et Nom de serveur

#include "../commands.hpp"

void u_user(SockServer& srv, std::vector<std::string> args, User& user) {
	if (args[0] != "USER" || args.size() < 5)
		return ;
	user.user = args[1];
	if (*args[4].begin() == ':') //Le nom réel doit commencer par : et peut contenir des espaces
		user.realName = args[4];
	else
		return ;
	for (int i = 5; i < args.size(); i++) {
		user.realName += " " + args[i];
	}
}