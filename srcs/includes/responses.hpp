//
// Created by mlabouri on 6/23/22.
//

#ifndef RESPONSES_HPP
#define RESPONSES_HPP

#define RPL_WELCOME(nick, username) ":ircserv 001 " + nick + " :Welcome to ft_irc " + nick + "!" + username + "@ircserv.42"

#define TOPIC(nick, channel) ":ircserv 332 " + nick + " " + channel + " :"
#define NOTOPIC(nick, channel) ":ircserv 331 " + nick + " "  + channel + " :No topic is set"

#define TIME(nick, time) ":ircserv 391 " + nick + " ircserv :" + time
#define VERSION(nick, version) ":ircserv 351 " + nick + " ircserv " + version + " :latest commit"
#define INFO(nick, info) ":ircserv 371 " + nick + " ircserv :" + info
#define ENDOFINFO(nick) ":ircserv 374 " + nick + " ircserv :End of INFO list"
#define NAMES(nick, channel) ":ircserv 353 " + nick + " = " + channel + " :"
#define ENDOFNAMES(nick, channel) ":ircserv 366 " + nick + " " + channel + " :End of NAMES list"
#define LIST(nick, channel, memberCount) ":ircserv 322 " + nick + " " + channel + " " + memberCount + " :"
#define LISTEND(nick) ":ircserv 323 " + nick + " :End of LIST"
#define ERROR_QUIT(nick, ip, reason) "ERROR :Closing Link " + nick + "[" + ip + "] (" + reason + ":: " + nick + ")"

#define WHOREPLY(userNick, channel, user, nick, operStatus, realName) ":ircserv 352 " + userNick + " " + channel + " " + user + " ircserv.42 ircserv " + nick + " H" + operStatus + " :0 " + realName
#define ENDOFWHO(nick, arg, match) ":ircserv 315 " + nick + " " + arg + " :End of WHO list by " + match

#define CHANNELMODEIS(nick, channel) ":ircserv 324 " + nick + " " + channel + " "
#define UMODEIS(nick, target) ":ircserv 221 " + nick + " " + target + " "

#define YOUREOPER(nick) ":ircserv 381 " + nick + " :You are now an IRC operator"
#define CHANOPER(channel, to) ":ircserv PRIVMSG " + channel + " :" + to + " now has godly powers\n"
#define CHANNOOPER(channel, to) ":ircserv PRIVMSG " + channel + " :" + to + " is just a boring human\n"
#define CHANNLASTOPER(channel, to) ":ircserv PRIVMSG " + channel + " :" + to + " can't do that, you are the last man standing\n"

#define NICK(nick, username) ":" + nick + "!" + username + "@ircserv.42" + " NICK :"
#define QUIT(nick, username) ":" + nick + "!" + username + "@ircserv.42" + " QUIT :"
#define JOIN(nick, username, channel) ":" + nick + "!" + username + "@ircserv.42" + " JOIN " + channel
#define PART(nick, username, channel) ":" + nick + "!" + username + "@ircserv.42" + " PART " + channel + " :"
#define PRIVMSG(nick, username, to) ":" + nick + "!" + username + "@ircserv.42 PRIVMSG " + to + " :"
#define MODE(nick, username) ":" + nick + "!" + username + "@ircserv.42 MODE "
#define KILL(nick, username) ":" + nick + "!" + username + "@ircserv.42 KILL "
#define KICK(nick, username) ":" + nick + "!" + username + "@ircserv.42 KICK "

#define RPL_ENDOFINVITELIST(nick, channel) ":ircserv 347 " + nick + " " + channel + " :End of channel invite list"
#define RPL_ENDOFEXCEPTLIST(nick, channel) ":ircserv 349 " + nick + " " + channel + " :End of channel exception list"
#define RPL_ENDOFBANLIST(nick, channel) ":ircserv 368 " + nick + " " + channel + " :End of channel ban list"

#endif //RESPONSES_HPP
