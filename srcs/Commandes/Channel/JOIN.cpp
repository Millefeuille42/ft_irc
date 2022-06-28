//Rejoindre un canal.
//JOIN <canal>{,<canal>} [<clé>{,<clé>}]
//Un channel commence par # ou &

#include "../../includes/SockServer.hpp"

//Peut rejoindre plusieurs channels en même temps, séparé par des virgules (Pareil pour les clés)

void parseChan(std::map<std::string, std::string>& mChans, std::vector<std::string>& args) {
	std::string::iterator it = args[1].begin();
	std::string::iterator ite = it;
	std::string::iterator itk = args[2].begin();
	std::string::iterator itek = itk;
	while (it != args[1].end()) {
		std::string chan;
		while (ite != args[1].end() || *ite != ',')
			ite++;
		chan.assign(it, ite);
		mChans[chan] = "";
		if (args.size() == 3) {
			std::string key;
			while (itek != args[2].end() || *itek != ',')
				itek++;
			key.assign(itk, itek);
			if (key != "x")
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
	//Parser les channels et leur clé. Donc vérifier si la commande est bien JOIN,
	if (args[0] != "JOIN" || args.size() <= 1)
		return ;
	//Puis tant qu'il y a des virgules stocker dans un vector de string (?) les noms des channels.
	//Faire pareil avec les clés
	//Pourquoi pas faire une map avec les channels et les clés ?
	std::map<std::string, std::string> mChans;
	parseChan(mChans, args);
	//Verifier si le(s) channel commence par # ou & (IRSSI les envoie avec # par défault)
	//Mettre le User dans le channel, s'il existe, sinon le créer avec le User en creator
	//Vérifier, si le channel existait, si la clé correspond.
	//Mettre le channel dans le user, en théorie, IRSSI n'envoie pas si le user est déjà dans le channel
	//Mettre le channel sur le serveur s'il existe
	for (std::map<std::string, std::string>::iterator it = mChans.begin(); it != mChans.end() ; it++) {
		channelsMap::iterator itc = srv._chans.find(it->first);
		if (itc == srv._chans.end()) { //Nouveau Channel
			Channels newC = Channels(user.fd, it->first, it->second);
			user.enterChannel(&newC, true);
		}
		else {
			if (itc->second->joinChannel(user.fd, it->second)) {  //Channel rejoins
				user.enterChannel(itc->second, false); //TODO Message de bienvenue dans le Channel
			}
			else { //Channel Non-Rejoins
				srv.sendMessage(user.fd, "You can't join this channel", std::cerr);
			}
		}
	}
}
//TODO Mode Invit a ajouter
