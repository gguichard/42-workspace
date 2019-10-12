# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 11:39:36 by gguichar          #+#    #+#              #
#    Updated: 2019/10/10 16:15:43 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	computorv1

END		=	\x1b[0m
GREEN	=	\x1b[32m

INC_DIR	=	includes

CC		=	gcc
CFLAGS 	=	-Wall -Werror -Wextra -I $(INC_DIR)
LDFLAGS	=
LDLIBS	=

SRC_DIR	=	src
SRC 	=		\
error.c			\
lexer.c			\
lexer_types.c	\
main.c			\
parser.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@/bin/mkdir $(OBJ_DIR) 2> /dev/null || true

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
