# Placeholder de makefile
NAME	=	ircserv

CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
FLAGS_S	=	-g -fsanitize=address

SRCS	=	srcs/_SockServer_Commands.cpp \
		srcs/utils.cpp \
		srcs/SockServer.cpp \
		srcs/main.cpp \
		srcs/User.cpp \
		srcs/socketConf.cpp \
		srcs/SockAddress.cpp \
		srcs/Commandes/Server/INFO.cpp \
		srcs/Commandes/Server/TIME.cpp \
		srcs/Commandes/Server/VERSION.cpp \
		srcs/Commandes/Users/PASS.cpp \
		srcs/Commandes/Users/QUIT.cpp \
		srcs/Commandes/Users/USER.cpp \
		srcs/Commandes/Users/NICK.cpp \
		srcs/Commandes/Users/MODE.cpp \
		srcs/Commandes/Users/OPER.cpp \
		srcs/Commandes/Requests/WHO.cpp \
		srcs/Commandes/Messages/PRIVMSG.cpp \
		srcs/Commandes/Channel/KICK.cpp \
		srcs/Commandes/Channel/TOPIC.cpp \
		srcs/Commandes/Channel/JOIN.cpp \
		srcs/Commandes/Channel/MODE.cpp \
		srcs/Commandes/Channel/INVITE.cpp \
		srcs/Commandes/Channel/LIST.cpp \
		srcs/Commandes/Channel/NAMES.cpp \
		srcs/Commandes/Channel/PART.cpp \
		srcs/Commandes/Other/KILL.cpp \
		srcs/Commandes/Other/PING.cpp \
		srcs/Commandes/Other/ERROR.cpp


OBJS	=	$(SRCS:.cpp=.o)

$(NAME):	all

all:	$(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

sanitize:	$(OBJS)
			$(CC) $(FLAGS) $(FLAGS_S) $(OBJS) -o $(NAME)_san

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re:	fclean all

%.o:	%.cpp
		$(CC) $(FLAGS) -o $@ -c $<

.PHONY: all clean fclean re
