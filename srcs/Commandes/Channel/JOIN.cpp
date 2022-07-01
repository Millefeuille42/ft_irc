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
	if (args[0] != "JOIN" || args.size() <= 1)
		return ;
	std::map<std::string, std::string> mChans;

	parseChan(mChans, args);

	for (std::map<std::string, std::string>::iterator it = mChans.begin(); it != mChans.end() ; it++) {
		channelsMap::iterator itc = srv._chans.find(it->first);
		std::string mess = "Welcome in the channel " + it->first + "!\n";
		if (itc == srv._chans.end()) { //Nouveau Channel
			Channels newC = Channels(user.fd, it->first, it->second);
			user.enterChannel(&newC, true);
			srv._chans[it->first] = &newC;
			srv.sendMessage(user.fd, mess, std::cout);
		}
		else {
			if (itc->second->joinChannel(user.fd, it->second)) {  //Channel rejoins
				user.enterChannel(itc->second, false); //TODO Message de bienvenue dans le Channel
				srv.sendMessage(user.fd, mess, std::cout);
			}
			else { //Channel Non-Rejoins
				srv.sendMessage(user.fd, "You can't join this channel", std::cerr);
			}
		}
	}
}
//TODO Mode Invit a ajouter
