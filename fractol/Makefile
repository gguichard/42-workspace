# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/02/11 05:43:22 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

SRC_DIR	=	src
SRC		=	main.c \
lib.c \
lib_hooks.c \
draw.c \
draw_gpu.c \
fractals.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)

INC_DIR	=	includes

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I libft/includes -I $(INC_DIR)
LIBS	=	-L /usr/local/lib -lmlx -framework OpenCL -framework OpenGL -framework AppKit

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
