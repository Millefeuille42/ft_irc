//
// Created by mlabouri on 6/3/22.
//

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <sys/socket.h>
#include <netinet/in.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <poll.h>
#include <cstring>

# define ANY_CLIENT INADDR_ANY // Correspond a 0.0.0.0
# define IPV4 AF_INET // Correspond a Ipv4 quand utilisé
# define TCP SOCK_STREAM // Correspond au protocole TCP
# define IP_PROTOCOL 0
# define MAX_CLIENTS 3

int socketConf(char *port);

#endif //FT_IRC_HPP
