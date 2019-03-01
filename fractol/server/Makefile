# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/03/01 22:32:48 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol_server

SRC_DIR	=	src
SRC		=		\
main.c			\
server.c		\
compute.c		\
compress.c		\
utils.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)

INC_DIR	=	includes

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O2 -I libft/includes -I $(INC_DIR)
LIBS	=	-L /usr/local/lib -framework OpenCL

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) $(LIBS) -o $@ $^

$(LIBFT):
	$(MAKE) -C libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

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
