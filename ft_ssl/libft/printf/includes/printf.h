/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 20:40:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 13:44:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <string.h>
# include <stdarg.h>
# include <wchar.h>

# define PRINTF_BUF 512

/*
** FLAGS
** modifie le resulat d'une conversion
*/
# define HASH_FLAG 0x1
# define ZERO_FLAG 0x2
# define MINUS_FLAG 0x4
# define SPACE_FLAG 0x8
# define PLUS_FLAG 0x10

/*
** MODIFIERS
** change la facon dont les parametres sont recuperes
*/
# define HH_MODIFIER 0x20
# define H_MODIFIER 0x40
# define L_MODIFIER 0x80
# define LL_MODIFIER 0x100
# define LUP_MODIFIER 0x200
# define J_MODIFIER 0x400
# define Z_MODIFIER 0x800

/*
** PRINTF
*/
typedef struct		s_pf
{
	int				flags;
	int				w_field;
	int				precision;
	char			type;
	va_list			ap;
	int				fd;
	char			*buf;
	size_t			buf_off;
	int				buf_write;
	char			**ret;
}					t_pf;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);

/*
** PARSING
*/
int					pf_flag(t_pf *pf, const char **tok);
int					pf_modifier(t_pf *pf, const char **tok);
int					pf_precision(t_pf *pf, const char **tok);
int					pf_w_field(t_pf *pf, const char **tok);
void				pf_parse(t_pf *pf, const char *format);

/*
** BUFFER
*/
void				buf_write(t_pf *pf, const char *buf, size_t nbytes);
void				buf_pad(t_pf *pf);
void				buf_char(t_pf *pf, char c, size_t nbytes);

/*
** CONVERSIONS
*/
void				pf_conv_s(t_pf *pf);
void				pf_conv_c(t_pf *pf);
void				pf_conv_di(t_pf *pf);
void				pf_conv_u(t_pf *pf);
void				pf_conv_x(t_pf *pf);
void				pf_conv_o(t_pf *pf);
void				pf_conv_p(t_pf *pf);
void				pf_conv_misc(t_pf *pf);

/*
** CONV UTILS
*/
long long			pf_value(t_pf *pf);
unsigned long long	pf_uvalue(t_pf *pf);
void				pf_write_utf8(t_pf *pf, wint_t c);

#endif
