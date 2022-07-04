//Permet à un utilisateur de se déconnecter en laissant, ou non, un message
//QUIT [<Message de départ>]

#include "../../includes/SockServer.hpp"

void SockServer::quit(SockServer &srv, std::vector<std::string>& args, User& user) {
	if (args.empty() && args[0] != "QUIT")
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
	for (std::map<Channels*, bool>::iterator cit = user.channels.begin(); cit != user.channels.end(); cit++) {
		transmitToChannel(*cit->first, User(), PART(user.nick, user.user, cit->first->getName()) + "disconnected\n");
	}
	srv.transmit(User(), QUIT(user.nick, user.user) + mess, std::cout);
	srv.deleteClient(it);
}
