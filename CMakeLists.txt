cmake_minimum_required(VERSION 3.10)
project(ft_irc CXX)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++98")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -Wall -Werror -Wextra -pedantic -std=c++98")

add_executable(ft_irc
        srcs/main.cpp
		srcs/socketConf.cpp

		srcs/SockAddress.cpp
		srcs/SockServer.cpp srcs/includes/SockServer.hpp srcs/utils.cpp)