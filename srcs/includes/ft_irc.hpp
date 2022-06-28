//
// Created by mlabouri on 6/3/22.
//

#ifndef FT_IRC_HPP
#define FT_IRC_HPP


#include <unistd.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <cstring>

#include "User.hpp"
#include "Channels.hpp"
#include "responses.hpp"

# define ANY_CLIENT INADDR_ANY // Correspond a 0.0.0.0
# define IPV4 AF_INET // Correspond a Ipv4 quand utilisé
# define TCP SOCK_STREAM // Correspond au protocole TCP
# define IP_PROTOCOL 0
# define MAX_CLIENTS 50
# define DATA_IN POLLIN
# define BUFFER_SIZE 10

extern int g_servFd;

typedef std::vector<struct pollfd> fdVector;
typedef std::map<int, User> userMap;
typedef std::vector<std::string> stringVector;
typedef std::map<std::string, Channels*> channelsMap;

typedef fdVector::iterator fdIterator;
typedef fdVector::const_iterator const_fdIterator;

typedef struct pollfd t_pollfd;

int socketConf(const char *port);
struct pollfd generatePollFd(int fd, short events);
std::vector<std::string> parseMessage(std::string msg);

#endif //FT_IRC_HPP
