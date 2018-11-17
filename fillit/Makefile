# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 16:35:23 by gguichar          #+#    #+#              #
#    Updated: 2018/11/17 14:16:15 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fillit
SRC		= src/main.c src/parser.c src/resolver.c \
		  src/printit.c src/checks.c src/utils.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $^ libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
