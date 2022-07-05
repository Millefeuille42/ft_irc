//
// Created by mlabouri on 6/10/22.
//

#ifndef ERRORS_HPP
#define ERRORS_HPP

# define ERR_NOORIGIN(nick) ":ircserv 409 " + nick + " :No origin specified"

# define ERR_NONICKNAMEGIVEN(nick) ":ircserv 431 " + nick + " :No nickname given"
# define ERR_NONICKNAMEGIVEN_NONICK ":ircserv 431 :No nickname given"

# define ERR_ERRONEUSNICKNAME(nick) ":ircserv 432 " + nick + " :Erroneus nickname"

# define ERR_NICKNAMEINUSE(nick) ":ircserv 433 " + nick + " :Nickname is already in use"

# define ERR_NOTONCHANNEL(nick, channel) ":ircserv 442 " + nick + " " + channel + " :You're not on that channel"
# define ERR_CHANOPRIVSNEEDED(nick, channel) ":ircserv 482 " + nick + " " + channel + " :You're not channel operator"

# define ERR_NEEDMOREPARAMS(nick) ":ircserv 461 " + nick + " :Not enough parameters"
# define ERR_NEEDMOREPARAMS_NONICK ":ircserv 461 :Not enough parameters"

# define ERR_ALREADYREGISTERED(nick) ":ircserv 462 " + nick + " :You may not reregister"

# define ERR_PASSWDMISMATCH(nick) ":ircserv 464 " + nick + " :Password incorrect"

# define ERR_NOTEXTTOSEND(nick) ":ircserv 412 " + nick + " :No text to send"
# define ERR_NOSUCHNICK(nick, target) ":ircserv 401 " + nick + " " + target + " :No such nick"
# define ERR_NOSUCHCHANNEL(nick, target) ":ircserv 403 " + nick + " " + target + " :No such channel"


#endif //ERRORS_HPP
