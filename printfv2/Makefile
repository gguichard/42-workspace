# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 09:21:09 by gguichar          #+#    #+#              #
#    Updated: 2018/12/09 19:58:45 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	libftprintf.a

SRC		= 	ft_printf.c parse_tok.c parser.c buffer.c \
			conv_s.c conv_c.c conv_di.c conv_u.c conv_x.c conv_o.c conv_p.c \
			conv_misc.c conv_utils.c
SRC_DIR	= 	src

OBJ		= 	$(SRC:.c=.o)
OBJ_DIR	= 	.obj

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror -I libft/includes -I includes

LIBFT	= 	libft/libft.a

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	mv $(LIBFT) $@
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/printf.h  | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	/bin/mkdir $@

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
