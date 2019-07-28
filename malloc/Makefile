# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/07/28 14:32:53 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	malloc.so

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra -fPIC
LDFLAGS		=	-Llibft -lft

SRC_DIR		=	src
SRC 		=		\
blocks.c			\
malloc.c			\
regions.c			\
routines/free.c		\
routines/malloc.c	\
routines/realloc.c	\
utils.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) -shared -o $@ $^ $(LDFLAGS)
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true
	@mkdir $@/routines 2> /dev/null || true

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
