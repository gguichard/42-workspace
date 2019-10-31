# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/27 19:50:57 by gguichar          #+#    #+#              #
#    Updated: 2019/10/31 17:39:24 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	wolf3d

END				=	\x1b[0m
GREEN			=	\x1b[32m

INC_DIR			=	includes

SDL_LIB			=	SDL2-2.0.9
SDL_DIR			=	SDL2
SDL_TAR			=	$(SDL_LIB).tar.gz
SDL_BUILD		=	$(SDL_DIR)/lib/libSDL2.a

CC				=	gcc -O2
CPPFLAGS		=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 			=	-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS			=	-Llibft -lft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs)

SRC_DIR			=	src
SRC 			=	\
error.c				\
launch_ray.c		\
lib_sdl2.c			\
main.c				\
map_parser.c		\
map_parser_2.c		\
states/menu.c		\
states/play.c		\
texture.c			\
vec2d.c				\
vec2i.c				\
wolf3d.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(SDL_BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(SDL_BUILD): | $(SDL_DIR)
	curl https://www.libsdl.org/release/$(SDL_TAR) --output $(SDL_TAR)
	tar -xf $(SDL_TAR)
	cd $(SDL_LIB) && ./configure --prefix=$(shell pwd)/$(SDL_DIR)
	$(MAKE) -C $(SDL_LIB)
	$(MAKE) -C $(SDL_LIB) install

$(SDL_DIR):
	@mkdir $@ 2> /dev/null || true

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true
	@mkdir $@/states 2> /dev/null || true

clean:
	$(MAKE) -C libft clean
	$(RM) $(SDL_TAR)
	$(RM) -r $(SDL_LIB)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)
	$(RM) -r $(SDL_DIR)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
