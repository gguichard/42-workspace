# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/29 17:35:18 by gguichar          #+#    #+#              #
#    Updated: 2018/09/04 20:37:20 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
			ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
			ft_strnlen.c ft_strdup.c ft_strndup.c ft_strcpy.c \
			ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
			ft_strcmp.c ft_strncmp.c ft_atoi.c ft_atoi_base.c \
			ft_strtol.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
			ft_isspace.c ft_isupper.c ft_islower.c ft_strtoupper.c \
			ft_strtolower.c ft_memalloc.c ft_memdel.c ft_strnew.c \
			ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
			ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
			ft_strsub.c ft_strjoin.c ft_strjoin_free.c ft_strtrim.c \
			ft_strstrim.c ft_strreplace.c ft_strreplace_free.c ft_strsplit.c \
			ft_join.c ft_itoa.c ft_itoa_base.c ft_putchar.c \
			ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c \
			ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_lstnew.c \
			ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstpush.c \
			ft_lstpop.c ft_lstpeek.c ft_lstsize.c ft_lstempty.c \
			ft_lstiter.c ft_lstmap.c ft_min.c ft_max.c ft_abs.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
