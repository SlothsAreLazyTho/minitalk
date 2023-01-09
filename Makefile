# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cbijman <cbijman@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/15 12:42:06 by cbijman       #+#    #+#                  #
#    Updated: 2022/12/15 18:57:44 by cbijman       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = ft_client.c \
		ft_server.c

EXEC_CLIENT = client
EXEC_SERVER = server

#$(CC) ./src/ft_client.c ./libft/libft.a -Iinclude -o $(EXEC_CLIENT)

default: lib
	$(CC) ./src/ft_server.c ./libft/libft.a -Iinclude -o $(EXEC_SERVER)
	$(CC) test_client.c ./libft/libft.a -Iinclude -o client
	@echo "Compiled server & client"

lib:
	make -C libft

all: default

clean:
	make clean -C libft
	rm -rf $(EXEC_CLIENT) $(EXEC_SERVER)

fclean:
	make fclean -C libft