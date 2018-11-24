# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 08:54:00 by gguichar          #+#    #+#              #
#    Updated: 2018/11/24 11:13:33 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
SRC		= ft_ls.c options.c output.c sort_types.c flist.c utils.c
OBJ		= $(SRC:.c=.o)

LIBFT	= libft/libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I libft/includes/ -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all
