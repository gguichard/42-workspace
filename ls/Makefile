# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 08:54:00 by gguichar          #+#    #+#              #
#    Updated: 2018/11/29 15:22:36 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	ft_ls

SRC		= 	src/main.c src/options.c src/ft_ls.c \
			src/output.c src/output_columns.c src/output_list.c \
			src/flist.c src/flist_sort.c src/files.c \
			src/sort/name.c src/sort/time.c src/sort/size.c \
			src/file_utils.c src/utils.c
OBJ		= 	$(SRC:.c=.o)

LIBFT	= 	libft/libft.a

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c includes/ft_ls.h
	$(CC) $(CFLAGS) -I libft/includes/ -I includes/ -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
