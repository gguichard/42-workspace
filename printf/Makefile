# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2018/11/22 15:37:54 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
SRC		= printf.c parser.c  tokens.c  buffer.c \
		  convert_str.c convert_int.c convert_double.c convert_misc.c \
		  utf8_utils.c int_utils.c utils.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	mv $(LIBFT) $@
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I libft/ -o $@ -c $<

clean:
	$(MAKE) -C libft/ clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
