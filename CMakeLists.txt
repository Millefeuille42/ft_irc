cmake_minimum_required(VERSION 3.10)
project(ft_irc CXX)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++98")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -Wall -Werror -Wextra -pedantic -std=c++98")

add_executable(ft_irc
		srcs/main.cpp

		srcs/utils.cpp
		srcs/User.cpp
		srcs/socketConf.cpp
		srcs/SockAddress.cpp
		srcs/_SockServer_Commands.cpp
		srcs/SockServer.cpp

		srcs/Commandes/Server/INFO.cpp
		srcs/Commandes/Server/TIME.cpp
		srcs/Commandes/Server/VERSION.cpp

		srcs/Commandes/Users/PASS.cpp
		srcs/Commandes/Users/QUIT.cpp
		srcs/Commandes/Users/USER.cpp
		srcs/Commandes/Users/NICK.cpp
		srcs/Commandes/Users/MODE.cpp
		srcs/Commandes/Users/OPER.cpp

		srcs/Commandes/Requests/WHO.cpp

		srcs/Commandes/Messages/PRIVMSG.cpp

		srcs/Commandes/Channel/KICK.cpp
		srcs/Commandes/Channel/TOPIC.cpp
		srcs/Commandes/Channel/JOIN.cpp
		srcs/Commandes/Channel/MODE.cpp
		srcs/Commandes/Channel/INVITE.cpp
		srcs/Commandes/Channel/LIST.cpp
		srcs/Commandes/Channel/NAMES.cpp
		srcs/Commandes/Channel/PART.cpp

		srcs/Commandes/Other/KILL.cpp
		srcs/Commandes/Other/PING.cpp
		srcs/Commandes/Other/ERROR.cpp

		)