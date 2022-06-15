# Placeholder de makefile
NAME	=	ircserv

CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
FLAGS_S	=	-g -fsanitize=address

SRCS	=	srcs/main.cpp \
			srcs/SockAddress.cpp \
			srcs/socketConf.cpp \
			srcs/SockServer.cpp \
			srcs/utils.cpp \

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