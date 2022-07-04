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
	std::string tokilluser = args[1];

	// if (user a pas les droits batard ( pas ircoperate))
	// {
	//	std::cerr << "Error: Don't have this privilege" << std::endl; IL FAUT CE CHECK MAIS JE SAIS PAS COMMENT ON SAIT QUI EST OPERATE //TODO
	// }
	// remplacer le if en dessous par un else if
	if (args.size() < 2)
	{
		std::cerr << "Error: Need param" << std::endl;
	}
	else if (tokilluser == "ircserv")
	{
		std::cerr << "Error: Server couldn't be killed" << std::endl;
	}
	else if (!srv.getUserByNick(tokilluser) || !srv.getUserByRealName(tokilluser) || !srv.getUserByUsername(tokilluser))
	{
		std::cerr << "Error: Unknown user" << std::endl;
	}
	else
	{
		User *bastard = srv.getUserByUsername(tokilluser);
		srv.sendMessage(bastard->fd, bastard->nick + " have been kicked\n", std::cout);
		// srv.deleteClient(bastard->fd);
		user.nick.erase();
		user.user.erase();
		close(user.fd);
		std::cout.flush(); //TODO
	}
}
