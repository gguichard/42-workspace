/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:27:55 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/18 01:00:32 by gguichar         ###   ########.fr       */
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

typedef	unsigned long	t_intptr;

typedef struct			s_pholder
{
	int			flags;
	int			width_field;
	int			precision;
	int			modifiers;
	char		type;
}						t_pholder;

int				parse(const char *str, va_list args);

int				print_placeholder(t_pholder *holder, va_list args);

int				ft_printf(const char *format, ...);

char			padding_byte(t_pholder *holder);

char			*pad_string(char *str, char c, size_t width, int right);

int				base_from_type(t_pholder *holder);

char			*decimal_from_type(t_pholder *holder, va_list args);

char			*str_prepend(char *s1, char *s2);

char			*convert_str(t_pholder *holder, va_list args);

char			*convert_char(t_pholder *holder, va_list args);

char			*convert_decimal(t_pholder *holder, va_list args);

char			*convert_double(t_pholder *holder, va_list args);

char			*convert_pointer(t_pholder *holder, va_list args);

#endif
