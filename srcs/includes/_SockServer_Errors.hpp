//
// Created by mlabouri on 6/10/22.
//

#ifndef _SOCKSERVER_ERRORS_HPP
#define _SOCKSERVER_ERRORS_HPP

# define ERR_NONICKNAMEGIVEN ":ircserv 431 :No nickname given\n"
# define ERR_ERRONEUSNICKNAME(x) ":ircserv 432 " + x + " :Erroneus nickname\n"
# define ERR_NICKNAMEINUSE(x) ":ircserv 433 " + x + " :Nickname is already in use\n"

# define ERR_NEEDMOREPARAMS(x) ":ircserv 461 " + x + " :Not enough parameters\n"
# define ERR_ALREADYREGISTERED ":ircserv 462 :You may not reregister\n"


#endif //_SOCKSERVER_ERRORS_HPP
