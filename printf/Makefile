# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2018/11/16 23:59:38 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
SRC		= printf.c parser.c convert.c convert_utils.c utils.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft/
	ar rcs $@ $^ libft/*.o

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