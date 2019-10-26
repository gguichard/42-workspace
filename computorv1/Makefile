# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/10/26 20:03:02 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	computorv1

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	clang++ --std=c++17
CPPFLAGS	=	-I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra
LDFLAGS		=

SRC_DIR		=	src
SRC 		=	\
astnode.cpp		\
binaryop.cpp	\
complex.cpp		\
exprformula.cpp	\
lexer.cpp		\
main.cpp		\
math.cpp		\
number.cpp		\
parser.cpp		\
solver.cpp		\
token.cpp		\
unaryop.cpp

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.cpp=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
