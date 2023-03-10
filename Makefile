# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cbijman <cbijman@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/15 12:42:06 by cbijman       #+#    #+#                  #
#    Updated: 2023/02/22 17:44:51 by macbook       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

FILES = ft_client.c \
		ft_server.c

INCLUDE = ./include
LIBRARY = ./libft/libft.a 
HEADER = $(INCLUDE)/minitalk.h $(INCLUDE)/libft.h

NAME_CLIENT = client
NAME_SERVER = server

.c.o:
	$(CC) $(CFLAGS) -I$(INCLUDE) $(LIBRARY) $< -o $@

$(NAME_CLIENT): lib $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(LIBRARY) src/$(NAME_CLIENT).c -o $@

$(NAME_SERVER): lib $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(LIBRARY) src/$(NAME_SERVER).c -o $@

lib:
	make -C libft

all: lib $(NAME_CLIENT) $(NAME_SERVER)

clean:
	make clean -C libft
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

fclean:
	make fclean -C libft
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: $(NAME_CLIENT) $(NAME_SERVER) lib all clean fclean re