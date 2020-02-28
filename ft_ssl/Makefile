# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2020/02/28 11:06:44 by gguichar         ###   ########.fr        #
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
SRC 		=				\
hash/digest_print.c			\
hash/md5/md5_digest.c		\
hash/md5/md5_hash.c			\
hash/md5/md5_stream.c		\
hash/sha/sha1_digest.c		\
hash/sha/sha1_hash.c		\
hash/sha/sha1_stream.c		\
hash/sha/sha256_digest.c	\
hash/sha/sha256_hash.c		\
hash/sha/sha256_stream.c	\
hash/sha/sha512_digest.c	\
hash/sha/sha512_hash.c		\
hash/sha/sha512_stream.c	\
hash/stream.c				\
hash/stream_hash.c			\
interactive.c				\
main.c						\
options/hash_options.c		\
utils.c

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
	@mkdir -p $@/hash/md5 2> /dev/null || true
	@mkdir -p $@/hash/sha 2> /dev/null || true
	@mkdir $@/options 2> /dev/null || true

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
