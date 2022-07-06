//Transmettre une erreur aux opérateurs.
//ERROR < message d'erreur>
// ERROR :Closing Link: mllf[62.210.32.47] (Quit:: mllf)

#include "../../includes/SockServer.hpp"

void SockServer::error(const std::string& reason, User& user) {
	sendMessage(user.fd, ERROR_QUIT(user.nick, user.ip, reason) + "\n", std::cout);
}
