# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/09/22 19:29:43 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc -O2
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra
LDFLAGS		=	-Llibft -lft -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

SRC_DIR		=	src
SRC 		=			\
draw_fn.c				\
draw_utils.c			\
error.c					\
graphics.c				\
handle_hooks.c			\
hooks.c					\
key_hooks.c				\
lib_mlx.c				\
line_draw.c				\
main.c					\
math_utils.c			\
matrix44.c				\
palette.c				\
parser.c				\
parser_obj.c			\
utils.c					\
vectors.c				\
vline_draw.c			\
wf_obj_parser.c			\
wf_obj_parser_helper.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) $(LDFLAGS) -o $@ $^
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
	$(RM) $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
