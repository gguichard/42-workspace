# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2018/12/05 09:56:27 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_select

SRC		=	src/main.c src/choices.c src/select.c \
			src/events.c src/navigation.c src/search.c \
			src/utils.c
OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -ltermcap -I libft/includes -I includes -o $@ $^

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c includes/ft_select.h
	$(CC) $(CFLAGS) -I libft/includes -I includes -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
