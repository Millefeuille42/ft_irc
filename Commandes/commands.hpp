#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../srcs/includes/SockServer.hpp"
#include "../srcs/includes/User.hpp"
#include <vector>

void u_pass(SockServer& srv, std::vector<std::string> args, User& user); //PASS
void u_nick(SockServer& srv, std::vector<std::string> args, User& user); //NICK


#endif //COMMANDS_HPP
