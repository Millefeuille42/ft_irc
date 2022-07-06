//Rejoindre un canal.
//JOIN <canal>{,<canal>} [<clé>{,<clé>}]
//Un channel commence par # ou &

#include "../../includes/SockServer.hpp"

//Peut rejoindre plusieurs channels en même temps, séparé par des virgules (Pareil pour les clés)

void parseChan(std::map<std::string, std::string>& mChans, std::vector<std::string>& args) {
	std::string::iterator it = args[1].begin();
	std::string::iterator ite = it;
	std::string::iterator itk;
	std::string::iterator itek;
	if (args.size() == 3) {
		itk = args[2].begin();
		itek = itk;
	}

	while (it != args[1].end()) {
		std::string chan;
		while (ite != args[1].end() && *ite != ',') {
			ite++;
		}
		chan.assign(it, ite);
		mChans[chan] = "";
		if (args.size() == 3) {
			std::string key;
			while (itek != args[2].end() && *itek != ',')
				itek++;
			key.assign(itk, itek);
			if (key != "x") //TODO IRSSI envoie x en mdp s'il n'y en a pas
				mChans[chan] = key;
			if (*itek == ',')
				itek++;
			itk = itek;
		}
		if (*ite == ',')
			ite++;
		it = ite;
	}
}

void SockServer::join(SockServer &srv, std::vector<std::string>& args, User& user) {
	if (args[0] != "JOIN" || args.size() <= 1) {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick, args[0])) + "\n", std::cout);
		return;
	}
	std::map<std::string, std::string> mChans;

	parseChan(mChans, args);

	for (std::map<std::string, std::string>::iterator it = mChans.begin(); it != mChans.end() ; it++) {
		channelsMap::iterator itc = srv._chans.find(it->first);
		std::string mess = "Hello " + user.nick + "! Welcome in the channel " + it->first + "!\n";
		if (itc == srv._chans.end()) { //Nouveau Channel
			Channels newC(user.fd, it->first, it->second);
			srv._chans[it->first] = newC;
			user.enterChannel(&srv._chans[it->first], true);
			transmitToChannelFromServ(srv._chans[it->first], JOIN(user.nick, user.user, it->first) + "\n");
			if (!srv._chans[it->first].getTopic().empty()) {
				sendMessage(user.fd, TOPIC(user.nick, srv._chans[it->first].getName()) + srv._chans[it->first].getTopic() + "\n", std::cout);
			}
			std::vector<std::string> a;
			a.push_back("NAMES"); a.push_back(srv._chans[it->first].getName());
			names(srv, a, user);
			// TODO Cause un crash sans mode #channel
		}
		else {
			if (itc->second.isMode('i') == true) {
				std::cerr << itc->second.getName() << " is on invitation only" << std::endl;
				return ;
			}
			if (itc->second.joinChannel(user.fd, it->second)) {  //Channel rejoins
				user.enterChannel(&itc->second, false);
				transmitToChannelFromServ(itc->second, JOIN(user.nick, user.user, itc->first) + "\n");
				if (!itc->second.getTopic().empty()) {
					sendMessage(user.fd, TOPIC(user.nick, itc->second.getName()) + itc->second.getTopic() + "\n", std::cout);
				}
				std::vector<std::string> a;
				a.push_back("NAMES"); a.push_back(itc->second.getName());
				names(srv, a, user);
				// TODO Cause un crash sans mode #channel
			}
			else { //Channel Non-Rejoins
				sendMessage(user.fd, "You can't join this channel", std::cerr);
			}
		}
	}
}
//TODO Mode Invit a ajouter
