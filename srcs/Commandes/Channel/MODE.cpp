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

static void callFunctionChan(SockServer &srv, char mode, char ar, std::vector<std::string> args, Channels &chan, size_t &i) {
	std::string mess = "";
	//MODE <canal> +/-o <user>
	if (mode == 'o') {
		//Call Operator Function -> Envoyer args (Users)
		if (i >= args.size()) //Plus d'argument à envoyer
			return ;
		mess = chan.oMode(ar, srv.getUserByNick(args[i]));
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
	if (mess != "")
		srv.transmitToChannelFromServ(chan, mess);
}

static void callFunctionUser(SockServer &srv, char mode, char ar, User& user, bool op) {
	(void)srv;
	(void)ar;
	(void)user;
	(void)op;

	if (mode == 'i') {
		//Call Invisible Function
	}
	if (mode == 'o') {
		//Call Server Operator Function
	}
}

static void sendModesUser(SockServer &srv, User &user) {
	(void)srv;
	(void)user;
}

static void sendModesChan(SockServer &srv, Channels &chan, User& user) {
	static const std::string m = "iknlt";
	std::vector<std::string> modes;
	modes.push_back("");
	for (size_t i = 0; i < m.size(); i++) {
		if (chan.isMode(m[i]) == true) {
			if (modes[0] == "")
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
	if (modes[0] != "") {
		std::string mess = modes[0];
		for (size_t i = 1; i < modes.size(); i++)
			mess += " " + modes[i];

		(void)srv;
		(void)user;
		std::cerr << mess << std::endl;
	}
}

void SockServer::mode(SockServer &srv, std::vector<std::string> &args, User& user) {
	if (args[0] != "MODE" && args.size() <= 1)
		return ;

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
			if (c == ' ')
				return ; //Pas de + ou de -, donc ignorer la commande / message d'erreur
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
			std::cerr << "Not in channel" << std::endl;
			return;
		}
		if (chan->second.isOper(user.fd) == false) {
			std::cerr << "Not an operator" << std::endl;
			return ;
		}
		size_t j = 0;
		for (size_t i = 1; i < add.size(); i++) {
			callFunctionChan(srv, add[i], '+', argsV, chan->second, j);
		}
		for (size_t i = 1; i < rem.size(); i++) {
			callFunctionChan(srv, rem[i], '-', argsV,chan->second, j);
		}
	}

	else { //Mode pour User
		User *target = srv.getUserByNick(args[1]);
		if (!target) {
			std::cerr << "No such user" << std::endl;
			return;
		}
		if (args.size() == 2) {
			sendModesUser(srv, *target);
			return ;
		}
		for (size_t i = 1; i < add.size(); i++) {
			callFunctionUser(srv, add[i], '+', *target, user.modes['o']);
		}
		for (size_t i = 1; i < rem.size(); i++) {
			callFunctionUser(srv, rem[i], '-', *target, user.modes['o']);
		}
	}
}
