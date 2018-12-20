# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2018/12/20 13:42:01 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	push_swap

SRC		= 	main.c
SRC_DIR	= 	src

OBJ		= 	$(SRC:.c=.o)
OBJ_DIR	= 	.obj

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror -I ../libft/includes -I includes

LIBFT	= 	../libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT):
	$(MAKE) -C ../libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/push_swap.h  | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	/bin/mkdir $@

clean:
	$(MAKE) -C ../libft clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C ../libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
