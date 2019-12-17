# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/12/17 13:11:48 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ssl

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc -O2
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra
LDFLAGS		=	-Llibft -lft

SRC_DIR		=	src
SRC 		=			\
digest_print.c			\
interactive.c			\
main.c					\
md5/md5_digest.c		\
md5/md5_hash.c			\
md5/md5_hash_fn.c		\
md5/md5_stream.c		\
sha/sha1_digest.c		\
sha/sha1_hash.c			\
sha/sha1_hash_fn.c		\
sha/sha1_stream.c		\
sha/sha256_digest.c		\
sha/sha256_hash.c		\
sha/sha256_hash_fn.c	\
sha/sha256_hash_fn_2.c	\
sha/sha256_stream.c		\
sha/sha512_digest.c		\
sha/sha512_hash.c		\
sha/sha512_hash_fn.c	\
sha/sha512_hash_fn_2.c	\
sha/sha512_stream.c		\
options.c				\
stream.c				\
stream_hash.c			\
utils.c					\
utils_fn.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true
	@mkdir $@/md5 2> /dev/null || true
	@mkdir $@/sha 2> /dev/null || true

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
