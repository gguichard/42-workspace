# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/08/15 15:22:04 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	scop
MINILIBX	=	minilibx_macos

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc -g3 -fsanitize=address
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR) -Iminilibx_macos
CFLAGS 		=	-Wall -Werror -Wextra
LDFLAGS		=	-Llibft -lft -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit

SRC_DIR		=	src
SRC 		=	\
error.c			\
hooks.c			\
lib_mlx.c		\
main.c			\
shader.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(MAKE) -C $(MINILIBX)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true

clean:
	$(MAKE) -C libft clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C $(MINILIBX) clean
	$(RM) $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
