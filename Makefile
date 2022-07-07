# Placeholder de makefile
NAME	=	ircserv

CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic
FLAGS_S	=	-g -fsanitize=address
FLAGS_OPT = -O3

SRCS	=	srcs/_SockServer_Commands.cpp \
		srcs/utils.cpp \
		srcs/SockServer.cpp \
		srcs/main.cpp \
		srcs/User.cpp \
		srcs/socketConf.cpp \
		srcs/SockAddress.cpp \
		srcs/Channels.cpp \
		srcs/Commandes/Server/INFO.cpp \
		srcs/Commandes/Server/TIME.cpp \
		srcs/Commandes/Server/VERSION.cpp \
		srcs/Commandes/Users/PASS.cpp \
		srcs/Commandes/Users/QUIT.cpp \
		srcs/Commandes/Users/USER.cpp \
		srcs/Commandes/Users/NICK.cpp \
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
OBJS_SAN	=	$(SRCS:.cpp=.san.o)
OBJS_OPT	=	$(SRCS:.cpp=.opt.o)

all: $(NAME) version
opt: $(NAME)_opt version
san: $(NAME)_san version

$(NAME): $(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)
$(NAME)_san:	$(OBJS_SAN)
			$(CC) $(FLAGS) $(FLAGS_S) $(OBJS_SAN) -o $(NAME)_san
$(NAME)_opt:	$(OBJS_OPT)
			$(CC) $(FLAGS) $(FLAGS_OPT) $(OBJS_OPT) -o $(NAME)_opt

clean:
		rm -rf $(OBJS) $(OBJS_SAN) $(OBJS_OPT)

fclean: clean
		rm -rf $(NAME) $(NAME)_san $(NAME)_opt

re:	fclean all

version:
	@rm -f version.txt
	@git log --format="%H" -n 1 > version.txt
	@echo "version dumped"

%.o:	%.cpp
		$(CC) $(FLAGS) -o $@ -c $<
%.san.o:	%.cpp
		$(CC) $(FLAGS) $(FLAGS_S) -o $@ -c $<
%.opt.o:	%.cpp
		$(CC) $(FLAGS) $(FLAGS_OPT) -o $@ -c $<


.PHONY: all clean fclean re
