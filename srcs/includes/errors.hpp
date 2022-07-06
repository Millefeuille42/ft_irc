//
// Created by mlabouri on 6/10/22.
//

#ifndef ERRORS_HPP
#define ERRORS_HPP

# define ERR_NOORIGIN(nick) ":ircserv 409 " + nick + " :No origin specified"

# define ERR_NONICKNAMEGIVEN(nick) ":ircserv 431 " + nick + " :No nickname given"
# define ERR_NONICKNAMEGIVEN_NONICK ":ircserv 431 * :No nickname given"

# define ERR_NICKNAMEINUSE(nick) ":ircserv 433 * " + nick + " :Nickname is already in use"

# define ERR_NOTONCHANNEL(nick, channel) ":ircserv 442 " + nick + " " + channel + " :You're not on that channel"
# define ERR_USERONCHANNEL(nick, target, channel) ":ircserv 443 " + nick + " " + target + " " + channel + " :is already on channel"
# define ERR_USERNOTINCHANNEL(nick, target, channel) ":ircserv 441 " + nick + " " + target + " " + channel + " :They aren't on that channel"
# define ERR_CHANOPRIVSNEEDED(nick, channel) ":ircserv 482 " + nick + " " + channel + " :You're not channel operator"
# define ERR_NOPRIVILEGES(nick) ":ircserv 481 " + nick + " :Permission Denied- You're not an IRC operator"

# define ERR_USERSDONTMATCH(nick) ":ircserv 502 " + nick + " :Cannot change mode for other users"
# define ERR_UMODEUNKNOWNFLAG(nick) ":ircserv 501 " + nick + " :Unknown MODE flag"

# define ERR_NEEDMOREPARAMS(nick, command) ":ircserv 461 " + nick +  + " " + command +  " :Not enough parameters"
# define ERR_NEEDMOREPARAMS_NONICK(command) ":ircserv 461 * " + command + " :Not enough parameters"

# define ERR_ALREADYREGISTERED(nick) ":ircserv 462 " + nick + " :You may not reregister"

# define ERR_PASSWDMISMATCH(nick) ":ircserv 464 " + nick + " :Password incorrect"

# define ERR_NOTEXTTOSEND(nick) ":ircserv 412 " + nick + " :No text to send"
# define ERR_NOSUCHNICK(nick, target) ":ircserv 401 " + nick + " " + target + " :No such nick"
# define ERR_NOSUCHCHANNEL(nick, target) ":ircserv 403 " + nick + " " + target + " :No such channel"

# define ERR_INVITEONLYCHAN(nick, channel)":ircserv 473 " + nick + " " + channel + " :Cannot join channel (+i)"
# define ERR_BADCHANNELKEY(nick, channel)":ircserv 475 " + nick + " " + channel + " :Cannot join channel (+k)"
# define ERR_CHANNELISFULL(nick, channel)":ircserv 471 " + nick + " " + channel + " :Cannot join channel (+l)"

#endif //ERRORS_HPP
