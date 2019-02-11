# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/02/10 22:49:19 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

SRC		=	src/main.c \
			src/lib.c src/lib_hooks.c \
			src/draw.c \
			src/fractals.c
OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -Ofast
LIBS	=	-L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LIBS) -o $@ $^

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c includes/fractol.h
	$(CC) $(CFLAGS) -I libft/includes -I includes -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
