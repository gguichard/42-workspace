# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 15:19:40 by gguichar          #+#    #+#              #
#    Updated: 2018/11/30 13:00:40 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRC		=	src/main.c src/input.c src/env.c \
			src/path.c src/builtin.c src/utils.c
OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -I libft/includes/ -I includes/ -o $@ $^

$(LIBFT):
	$(MAKE) -C libft/

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -I libft/includes/ -I includes/ -c $< -o $@

clean:
	$(MAKE) -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
