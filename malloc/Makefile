# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/10/25 10:10:32 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft_malloc_$(HOSTTYPE).so
SYMLINK		=	libft_malloc.so

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra -fPIC
LDFLAGS		=	-Llibft -lft

SRC_DIR		=	src
SRC 		=					\
allocs.c						\
block_utils.c					\
free_list.c						\
malloc.c						\
malloc_info.c					\
regions.c						\
routines/free.c					\
routines/malloc.c				\
routines/malloc_size.c			\
routines/realloc.c				\
routines/show_alloc_mem_hex.c	\
routines/show_alloc_mem.c		\
utils.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(SYMLINK)

$(SYMLINK): $(NAME)
	ln -sf $< $@

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) -shared -o $@ $^ $(LDFLAGS)
	$(MAKE) $(SYMLINK)
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
	$(RM) $(SYMLINK)
	$(RM) $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
