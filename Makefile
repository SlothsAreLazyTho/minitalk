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

default: libft
	$(CC) ./src/ft_client.c ./libft/libft.a -Iinclude -o $(EXEC_CLIENT)
	$(CC) ./src/ft_server.c ./libft/libft.a -Iinclude -o $(EXEC_SERVER)
	@echo "Compiled server & client"

lib:
	make -C libft

test:
	$(CC) test_client.c ./libft/libft.a -Iinclude -o client

clean:
	make clean -C libft
	rm -rf $(EXEC_CLIENT) $(EXEC_SERVER)