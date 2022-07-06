//Modifier le mode d'un channel
//MODE <canal>/<user> {[+|-]|o|i|t|n|b|l|k} [<limite>] [<utilisateur>] [<masque de bannissement >]

//o -> Rend l'utilisateur operateur de channel. Donc verifier que l'envoyeur est operateur de channel.
//i -> Rend le Channel sur invitation uniquement. Verifier que l'envoyeurr est op de channel.
//t -> Rend le topic modifiable uniquement par un operateur. Verifier que l'envoyeur est op de channel.
//n -> Impossible d'envoyer des messages sans etre dans le channel.
//b -> Bannir/Debannir un utilisateur du channel. Verifier si l'envoyeur est op de channel
//l -> Ajouter/Retier/Modifier un nombre limite d'utilisateur
//k -> Aouter/Retirer un cle de channel


//i -> Invisible
//o -> Operator

#include "../../includes/SockServer.hpp"

static void callFunctionChan(SockServer &srv, char mode, char ar, std::vector<std::string> args, Channels &chan, size_t &i, User &user) {
	std::string mess = "";
	//MODE <canal> +/-o <user>
	if (mode == 'o') {
		//Call Operator Function -> Envoyer args (Users)
		if (i >= args.size()) //Plus d'argument à envoyer
			return ;
		User *target = srv.getUserByNick(args[i]);
		if (target == NULL) {
			SockServer::sendMessage(user.fd, std::string(ERR_NOSUCHNICK(user.nick, args[i])) + "\n", std::cout);
			return;
		}
		mess = chan.oMode(ar, target);
		if (ar == '+')
			SockServer::transmitToChannelFromServ(chan, CHANOPER(chan.getName(), target->nick));
		i++;
	}
	//MODE <canal> +/-i
	else if (mode == 'i') {
		//Call Invitation Function
		chan.allModes(ar, mode);
		if (ar == '+')
			mess = chan.getName() + " is now on invitation only\n";
		else
			mess = chan.getName() + " is not on invitation only\n";
	}
	//MODE <canal> +/-t
	else if (mode == 't') {
		//Call TopicMode Function
		chan.allModes(ar, mode);
		if (ar == '+')
			mess = "Topic of " + chan.getName() + " can't be changed by everyone\n";
		else
			mess = "Topic of " + chan.getName() + " can be changed by everyone\n";
	}
	//MODE <canal> +/-n
	else if (mode == 'n') {
		//Call LimitedChan Function
		chan.allModes(ar, mode);
		if (ar == '+')
			mess = "Only member of the channel " + chan.getName() + " can send messages\n";
		else
			mess = "Everbody can send messages in the channel " + chan.getName() + "\n";
	}
	//MODE <canal> +/-l <Nb Limite>
	else if (mode == 'l') {
		//Call LimiteUser Function -> Envoyer args (Nombre limite)
		if (ar == '-') {
			chan.lMode(ar);
			return ;
		}
		if (i >= args.size()) //Plus d'argument à envoyer
			return ;
		for (size_t j = 0; j < args[i].size(); j++) {
			if (std::isdigit(args[i][j]) == 0) {
				mess = args[i] + " is not a number";
				i++;
				srv.transmitToChannelFromServ(chan, mess);
				return ;
			}
		}
		mess = chan.lMode(ar, atoi(args[i].c_str()), args[i]);
		i++;
	}
	//MODE <canal> +/-k <Key>
	else if (mode == 'k') {
		//Call Key Function -> Envoyer args )(Key)
		if (ar == '-') {
			chan.kMode(ar);
			return ;
		}
		if (i >= args.size()) //Plus d'argument à envoyer
			return ;
		mess = chan.kMode(ar, args[i]);
		i++;
	}
	std::cout << mess;
}

static bool callFunctionUser(SockServer &, char mode, char ar, User& target, User& user) {
	std::string mess = "";
	if (mode == 'i') {
		if (target.fd != user.fd) {
			SockServer::sendMessage(user.fd,
									ERR_USERSDONTMATCH(user.nick) + "\n",
									std::cerr);
			return false;
		}
		else if (ar == '+') {
			target.modes['i'] = true;
			mess = "Invisible mode actived for " + target.nick + "\n";
		}
		else if (ar == '-') {
			target.modes['i'] = false;
			mess = "Invisible mode not actived for " + target.nick + "\n";
		}
	} else if (mode == 'o') {
		if (user.modes['o'] == false)
			mess = "Not an operator\n";
		else if (ar == '+') {
			target.modes['o'] = true;
			mess = target.nick + " is now a global operator\n";
		}
		else if (ar == '-') {
			target.modes['o'] = false;
			mess = target.nick + " is not a global operator\n";
		}
	} else {
		SockServer::sendMessage(user.fd, ERR_UMODEUNKNOWNFLAG(user.nick) + "\n", std::cerr);
	}
	std::cout << mess;
	return true;
}

static void sendModesUser(SockServer &, User &target, User& user) {
	std::string mess = "";
	if (target.modes['o'] == true)
		mess.push_back('o');
	if (target.modes['i'] == true)
		mess.push_back('i');
	SockServer::sendMessage(user.fd, UMODEIS(user.nick, target.nick) + mess + "\n", std::cout);
}

static void sendModesChan(SockServer &, Channels &chan, User& user) {
	static const std::string m = "iknlt";
	std::vector<std::string> modes;
	modes.push_back("");
	for (size_t i = 0; i < m.size(); i++) {
		if (chan.isMode(m[i]) == true) {
			if (modes[0].empty())
				modes[0].push_back('+');
			modes[0].push_back(m[i]);
			if (m[i] == 'k') {
				modes.push_back(chan.getKey());
			}
			if (m[i] == 'l') {
				std::stringstream ss;
				ss << chan.getMaxMembers();
				modes.push_back(ss.str());
			}
		}
	}
	std::string mess;
	if (!modes[0].empty()) {
		mess = modes[0];
		for (size_t i = 1; i < modes.size(); i++)
			mess += " " + modes[i];
	}
	SockServer::sendMessage(user.fd, CHANNELMODEIS(user.nick, chan.getName()) + mess + "\n", std::cout);
}

static void filterInputs(std::vector<std::string> &args, User& user, const std::string &chan) {
	if (args.size() < 3)
		return;
	if (args[2] == "b") {
		SockServer::sendMessage(user.fd, RPL_ENDOFBANLIST(user.nick, chan) + "\n", std::cout);
	}
	else if (args[2] == "e") {
		SockServer::sendMessage(user.fd, RPL_ENDOFEXCEPTLIST(user.nick, chan) + "\n", std::cout);
	}
	else if (args[2] == "I") {
		SockServer::sendMessage(user.fd, RPL_ENDOFINVITELIST(user.nick, chan) + "\n", std::cout);
	}

}

void SockServer::mode(SockServer &srv, std::vector<std::string> &args, User& user) {
	if (args[0] != "MODE" && args.size() <= 1) {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick, args[0])) + "\n", std::cout);
		return;
	}

	std::vector<char> add(1, '+');
	std::vector<char> rem(1, '-');

	std::vector<std::string> argsV;

	char c = ' ';
	if (args.size() > 2)
		for (size_t i = 0; i < args[2].size(); i++) {
			if (args[2][i] == '+')
				c = '+';
			else if (args[2][i] == '-')
				c = '-';
			else if (c == '+')
				add.push_back(args[2][i]);
			else if (c == '-')
				rem.push_back(args[2][i]);
			if (c == ' ') {
				if (cInSet(args[1][0], "#&+!")) {
					std::map<std::basic_string<char>, Channels>::iterator chan = srv._chans.find(args[1]);
					if (chan == srv._chans.end()) {
						sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
						return;
					}
					filterInputs(args, user, chan->first);
					return;
				}
			}
		}

	for (size_t i = 3; i < args.size(); i++) {
		argsV.push_back(args[i]);
	}

	if (cInSet(args[1][0], "#&+!")) { //Mode pour channel
		std::map<std::basic_string<char>, Channels >::iterator chan = srv._chans.find(args[1]);
		if (chan == srv._chans.end()) {
			sendMessage(user.fd, std::string(ERR_NOSUCHCHANNEL(user.nick, args[1])) + "\n", std::cout);
			return;
		}
		if (args.size() == 2) {
			sendModesChan(srv, chan->second, user);
			return ;
		}
		if (!user.channels.count(&chan->second)) {
			sendMessage(user.fd, std::string(ERR_NOTONCHANNEL(user.nick, chan->first)) + "\n", std::cout);
			return;
		}
		if (chan->second.isOper(user.fd) == false) { //L'envoyeur n'est pas opérateur
			sendMessage(user.fd, std::string(ERR_CHANOPRIVSNEEDED(user.nick, chan->first)) + "\n", std::cout);
			return ;
		}
		size_t j = 0;
		for (size_t i = 1; i < add.size(); i++) {
			callFunctionChan(srv, add[i], '+', argsV, chan->second, j, user);
		}
		for (size_t i = 1; i < rem.size(); i++) {
			callFunctionChan(srv, rem[i], '-', argsV,chan->second, j, user);
		}
		std::string rep;
		for (std::vector<std::string>::iterator arg = args.begin() + 1; arg != args.end(); arg++)
			rep += *arg + " ";
		transmitToChannelFromServ(chan->second, MODE(user.nick, user.user) + rep + "\n");
	}

	else { //Mode pour User
		User *target = srv.getUserByNick(args[1]);
		if (!target) {
			sendMessage(user.fd, std::string(ERR_NOSUCHNICK(user.nick, args[1])) + "\n", std::cout);
			return;
		}
		if (args.size() == 2) {
			sendModesUser(srv, *target, user);
			return ;
		}
		for (size_t i = 1; i < add.size(); i++) {
			if (!callFunctionUser(srv, add[i], '+', *target, user))
				return;
		}
		for (size_t i = 1; i < rem.size(); i++) {
			if (!callFunctionUser(srv, rem[i], '-', *target, user))
				return;
		}
		std::string rep;
		for (std::vector<std::string>::iterator arg = args.begin() + 1; arg != args.end(); arg++)
			rep += *arg + " ";
		sendMessage(user.fd, MODE(user.nick, user.user) + rep + "\n", std::cout);
	}
}
