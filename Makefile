##
## EPITECH PROJECT, 2026
## my_ftp
## File description:
## Makefile
##

.PHONY: all clean fclean re lib

SRC =	src/main.c \
		src/server.c \
		src/manage_server.c \
		src/exec_commands.c \
		src/parser/parser.c \
		src/signal/signal.c \
		src/commands/commands.c \
		src/commands/command_reply.c \
		src/commands/unknown.c \
		src/commands/quit.c \

OBJ = $(SRC:.c=.o)

NAME = ecran_hub

CFLAGS = -I./include -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBS)

debug: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBS) -ggdb3

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
