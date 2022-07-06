//Lister les channels et leur sujet.
//LIST [<canal>{,<canal>}

#include "../../includes/SockServer.hpp"

static std::vector<std::string> parseMess(std::string msg)
{
	std::vector<std::string> args;
	size_t pos;
	std::string token;
	while ((pos = msg.find(',')) != std::string::npos)
	{
		token = msg.substr(0, pos);
		args.push_back(token);
		msg.erase(0, pos + 1);
	}
	args.push_back(msg);
	return args;
}

void SockServer::list(SockServer &srv, std::vector<std::string> & args, User& user)
{
	if (args.size() < 2) // en gros la c'est y a rien qui est dit donc on liste tous les chan et les gens dedans 1 par 1, et le dernier chan c'est la liste des gens qui sont nulpart et le chan s'apellerio (pas quezac) '*'
	{
		for (channelsMap::iterator it = srv._chans.begin(); it != srv._chans.end(); it++) {
			std::ostringstream ss(""); ss << it->second.getUsers().size();
			sendMessage(user.fd, LIST(user.nick, it->first, ss.str()) + it->second.getTopic() + "\n", std::cout);
		}
	}
	else // et la j'essaie de recuperer les channels qui ont ete envoye, separe par juste une virgule si il y en a + d'1, et ecrit avec un # devant
	{
		std::vector<std::string> chan_list = parseMess(args[1]);
		for (std::vector<std::string>::iterator i = chan_list.begin(); i != chan_list.end(); i++) {
			std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(*i);
			if (chan == srv._chans.end())
				return ;
			std::ostringstream ss(""); ss << chan->second.getUsers().size();
			sendMessage(user.fd, LIST(user.nick, chan->first, ss.str()) + chan->second.getTopic() + "\n", std::cout);
		}
	}
	sendMessage(user.fd, LISTEND(user.nick) + "\n", std::cout);
}
