# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 16:35:23 by gguichar          #+#    #+#              #
#    Updated: 2018/11/13 22:46:53 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fillit
SRC		= main.c get_line.c resolver.c printit.c checks.c utils.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -I libft/ -o $(NAME) $^ libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -I libft/ -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all
	$(MAKE) -C libft re

.PHONY: all clean fclean re
