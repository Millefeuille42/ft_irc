//Permet à un utilisateur de se déconnecter en laissant, ou non, un message
//QUIT [<Message de départ>]

#include "../../includes/SockServer.hpp"

void SockServer::quit(SockServer &srv, std::vector<std::string>& args, User& user) {
	if (args.size() < 1 && args[0] != "QUIT")
		return ;
	std::string mess = user.nick + " has quit";
	for (size_t i = 1; i < args.size(); i++) {
		if (i == 1) {
			mess += " :";
			args[i].erase(0,1);
		}
		mess += " " + args[i];
	}
	mess += "\n";
	fdVector::iterator it;
	for (it = srv._fds.begin(); it != srv._fds.end(); it++) {
		if (it->fd == user.fd)
			break ;
	}
	srv.deleteClient(it);
	srv.transmitServ(mess);
}
