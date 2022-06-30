//
// Created by mlabouri on 6/23/22.
//

#ifndef RESPONSES_HPP
#define RESPONSES_HPP

#define WELCOME(x,y) ":ircserv 001 " + x + " Welcome to ft_irc " + x + "! " + y + "@"
#define TIME(x) ":ircserv 391 ircserv :" + x
#define VERSION(x) ":ircserv 351 ircserv " + x + " :latest commit"

#define INFO(x) ":ircserv 351 ircserv " + x + " :latest commit"
#define ENDOFINFO(x) ":ircserv 351 ircserv " + x + " :latest commit"

#endif //RESPONSES_HPP
