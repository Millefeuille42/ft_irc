//
// Created by mlabouri on 6/23/22.
//

#ifndef RESPONSES_HPP
#define RESPONSES_HPP

//002    RPL_YOURHOST
//              "Your host is <servername>, running version <ver>"
//       003    RPL_CREATED
//              "This server was created <date>"
//       004    RPL_MYINFO
//              "<servername> <version> <available user modes>
//               <available channel modes>"

#define RPL_WELCOME(nick, username) ":ircserv 001 " + nick + " :Welcome to ft_irc " + nick + "!" + username + "@localhost"

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

#define CHANNELMODEIS(nick, channel) ":ircserv 324 " + nick + " " + channel + " "

#define YOUREOPER(nick) ":ircserv 381 " + nick + " :You are now an IRC operator"

#define NICK(nick, username) ":" + nick + "!" + username + "@localhost" + " NICK :"
#define QUIT(nick, username) ":" + nick + "!" + username + "@localhost" + " QUIT :"
#define JOIN(nick, username, channel) ":" + nick + "!" + username + "@localhost" + " JOIN " + channel
#define PART(nick, username, channel) ":" + nick + "!" + username + "@localhost" + " PART " + channel + " :"
#define PRIVMSG(nick, username, to) ":" + nick + "!" + username + "@localhost PRIVMSG " + to + " :"
#define MODE(nick, username) ":" + nick + "!" + username + "@localhost MODE "
#endif //RESPONSES_HPP
