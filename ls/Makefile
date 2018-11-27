# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 08:54:00 by gguichar          #+#    #+#              #
#    Updated: 2018/11/27 19:20:53 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	ft_ls

SRC		= 	main.c options.c ft_ls.c \
			output.c output_list.c sort_types.c \
			flist.c flist_sort.c files.c \
			file_utils.c utils.c
OBJ		= 	$(SRC:.c=.o)

LIBFT	= 	libft/libft.a

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c ft_ls.h
	$(CC) $(CFLAGS) -I libft/includes/ -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all
