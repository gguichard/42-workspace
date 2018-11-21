/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:27:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 16:16:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <string.h>
# include <stdarg.h>

# define HASH_FLAG 0x1
# define ZERO_FLAG 0x2
# define MINUS_FLAG 0x4
# define SPACE_FLAG 0x8
# define PLUS_FLAG 0x10

# define HH_MODIFIER 0x1
# define H_MODIFIER 0x2
# define L_MODIFIER 0x4
# define LL_MODIFIER 0x8
# define LUP_MODIFIER 0x10
# define Z_MODIFIER 0x20

# define WIDTH_WILDCARD 0x1
# define PRECISION_WILDCARD 0x2

typedef	unsigned long	t_intptr;

typedef struct	s_token
{
	int			flags;
	int			width_field;
	int			precision;
	int			modifiers;
	char		type;
	int			wildcards;
}				t_token;

typedef struct	s_buf
{
	char		*str;
	size_t		size;
}				t_buf;

int				tk_parse(t_token *tk, const char *str);

int				ft_printf(const char *format, ...);

char			padding_byte(t_token *token);

void			buf_pad(t_buf *buf, char pad, int width, int right_pad);

void			buf_prepend(char *s1, t_buf *buf);

void			convert_str(t_token *token, va_list ap, t_buf *buf);

void			convert_char(t_token *token, va_list ap, t_buf *buf);

void			convert_int(t_token *token, va_list ap, t_buf *buf);

void			convert_double(t_token *token, va_list ap, t_buf *buf);

void			convert_pointer(t_token *token, va_list ap, t_buf *buf);

void			convert_other(t_token *token, t_buf *buf);

#endif
