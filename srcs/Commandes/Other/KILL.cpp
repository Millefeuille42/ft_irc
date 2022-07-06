//Déconnecter un utilisateur du serveur
//KILL <pseudonyme> <commentaire>

// Command: KILL
// Parameters: <nickname> <comment>

// The KILL command is used to cause a client-server connection to be
// closed by the server which has the actual connection.  Servers
// generate KILL messages on nickname collisions.  It MAY also be
// available available to users who have the operator status.

// Clients which have automatic reconnect algorithms effectively make
// this command useless since the disconnection is only brief.  It does
// however break the flow of data and can be used to stop large amounts
// of 'flooding' from abusive users or accidents.  Abusive users usually
// don't care as they will reconnect promptly and resume their abusive
// behaviour.  To prevent this command from being abused, any user may
// elect to receive KILL messages generated for others to keep an 'eye'
// on would be trouble spots.

// In an arena where nicknames are REQUIRED to be globally unique at all
// times, KILL messages are sent whenever 'duplicates' are detected
// (that is an attempt to register two users with the same nickname) in
// the hope that both of them will disappear and only 1 reappear.

// When a client is removed as the result of a KILL message, the server
// SHOULD add the nickname to the list of unavailable nicknames in an
// attempt to avoid clients to reuse this name immediately which is
// usually the pattern of abusive behaviour often leading to useless
// "KILL loops".  See the "IRC Server Protocol" document [IRC-SERVER]
// for more information on this procedure.

// The comment given MUST reflect the actual reason for the KILL.  For
// server-generated KILLs it usually is made up of details concerning
// the origins of the two conflicting nicknames.  For users it is left
// up to them to provide an adequate reason to satisfy others who see
// it.  To prevent/discourage fake KILLs from being generated to hide
// the identify of the KILLer, the comment also shows a 'kill-path'
// which is updated by each server it passes through, each prepending
// its name to the path.

// Numeric Replies:

// ERR_NOPRIVILEGES   ERR_NEEDMOREPARAMS
// ERR_NOSUCHNICK     ERR_CANTKILLSERVER

// NOTE:
// It is RECOMMENDED that only Operators be allowed to kill other users
// with KILL command.  This command has been the subject of many
// controversies over the years, and along with the above
// recommendation, it is also widely recognized that not even operators
// should be allowed to kill users on remote servers.

#include "../../includes/SockServer.hpp"

void SockServer::kill(SockServer &srv, std::vector<std::string> &args, User& user)
{
	if (args.size() < 2 && args[0] != "KILL") {
		sendMessage(user.fd, std::string(ERR_NEEDMOREPARAMS(user.nick, args[0])) + "\n", std::cout);
		return;
	}

	if (user.modes['o'] == false) {
		sendMessage(user.fd, std::string(ERR_NOPRIVILEGES(user.nick)) + "\n", std::cout);
		return ;
	}

	std::string mess = "Reason";
	if (args[2] != ":")
		for (size_t i = 2; i < args.size(); i++) {
			if (i == 2) {
				mess += ":";
				args[i].erase(0,1);
			}
			mess += " " + args[i];
		}
	if (mess == "Reason")
		mess += " not provided";
	mess += "\n";

	User *u_kill = srv.getUserByNick(args[1]);
	if (!u_kill) {
		sendMessage(user.fd, std::string(ERR_NOSUCHNICK(user.nick, args[1])) + "\n", std::cout);
		return;
	}
	fdVector::iterator it;
	for (it = srv._fds.begin(); it != srv._fds.end(); it++) {
		if (it->fd == u_kill->fd)
			break ;
	}
	for (std::map<Channels*, bool>::iterator cit = u_kill->channels.begin(); cit != u_kill->channels.end(); cit++) {
		transmitToChannelFromServ(*cit->first, PART(u_kill->nick, u_kill->user, cit->first->getName()) + "disconnected\n");
		int fd_op = cit->first->leaveChannel(u_kill->fd);
		if (fd_op != -1) {
			srv._users[fd_op].channels[cit->first] = true;
			transmitToChannelFromServ(*cit->first, CHANOPER(cit->first->getName(), srv._users[fd_op].nick));
		}
		if (cit->first->isEmpty())
			srv._chans.erase(cit->first->getName());
	}
	u_kill->leaveAllChannels();
	std::string rep;
	for (std::vector<std::string>::iterator arg = args.begin() + 1; arg != args.end(); arg++)
		rep += *arg + " ";
	sendMessage(u_kill->fd, KILL(user.nick, user.user) + rep + "\n");
	srv.transmitServ(QUIT(u_kill->nick, u_kill->user) + mess);
	error("Kill", *u_kill);
	srv.deleteClient(it);
}
