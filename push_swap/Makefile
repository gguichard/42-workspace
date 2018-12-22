# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2018/12/21 13:25:14 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PS_NAME	= 	push_swap
CH_NAME	=	checker

PS_SRC	= 	push_swap.c parsing.c
CH_SRC	= 	checker.c parsing.c rotations.c apply_rots.c utils.c
SRC_DIR	= 	src

PS_OBJ	= 	$(PS_SRC:.c=.o)
CH_OBJ	= 	$(CH_SRC:.c=.o)
OBJ_DIR	= 	.obj

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror -I libft/includes -I includes

LIBFT	= 	libft/libft.a

all: $(PS_NAME) $(CH_NAME)

$(PS_NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(PS_OBJ))
	$(CC) $(CFLAGS) -o $@ $^

$(CH_NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(CH_OBJ))
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT):
	$(MAKE) -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	/bin/mkdir $@

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(PS_NAME)
	/bin/rm -f $(CH_NAME)

re: fclean all

.PHONY: all clean fclean re
