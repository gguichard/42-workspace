/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 23:13:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

static void	expand_buf(t_buf *buf)
{
	char	*tmp;

	tmp = buf->str;
	if (!(buf->str = (char *)malloc(sizeof(char) * (buf->size + PRINTF_BUF))))
		exit(1);
	if (tmp != NULL)
	{
		ft_memcpy(buf->str, tmp, buf->size);
		free(tmp);
	}
	buf->size += PRINTF_BUF;
}

static void	pf_wildcards(t_token *tok, va_list ap)
{
	int	tmp;

	if (tok->wildcards & WIDTH_WILDCARD)
	{
		tmp = va_arg(ap, int);
		if (tmp < 0 && tok->width_field < 0)
		{
			tmp = -tmp;
			tok->flags |= MINUS_FLAG;
		}
		tok->width_field = (tok->width_field < 0) ? tmp : tok->width_field;
	}
	if (tok->wildcards & PRECISION_WILDCARD)
	{
		tmp = va_arg(ap, int);
		tok->precision = (tok->precision < 0) ? tmp : tok->precision;
	}
}

static void	pf_convert(t_token *tok, t_buf *buf, va_list ap)
{
	pf_wildcards(tok, ap);
	if (tok->type == 'S' || tok->type == 'C'
		|| tok->type == 'D' || tok->type == 'O' || tok->type == 'U')
	{
		tok->type = ft_tolower(tok->type);
		tok->modifiers |= L_MODIFIER;
	}
	if (tok->type == 's')
		convert_str(tok, ap, buf);
	else if (tok->type == 'c')
		convert_char(tok, ap, buf);
	else if (tok->type == 'd' || tok->type == 'i'
		|| tok->type == 'o' || tok->type == 'u'
		|| tok->type == 'x' || tok->type == 'X')
		convert_int(tok, ap, buf);
	else if (tok->type == 'f' || tok->type == 'F')
		convert_double(tok, ap, buf);
	else if (tok->type == 'p')
		convert_pointer(tok, ap, buf);
	else if (tok->type != 0)
		convert_other(tok, buf);
}

static int	fill_buf(t_buf *buf, const char *str, va_list ap)
{
	int		len;
	t_token	token;
	t_buf	c_buf;

	len = 0;
	while (*str != '\0')
	{
		if (*str != '%')
		{
			if ((size_t)len >= buf->size)
				expand_buf(buf);
			(buf->str)[len++] = *str++;
		}
		else
		{
			str += tk_parse(&token, str + 1) + 1;
			if (token.type == 0)
				break ;
			str++;
			c_buf.str = NULL;
			c_buf.size = 0;
			pf_convert(&token, &c_buf, ap);
			while (len + c_buf.size > buf->size)
				expand_buf(buf);
			ft_memcpy(buf->str + len, c_buf.str, c_buf.size);
			free(c_buf.str);
			len += c_buf.size;
		}
	}
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	va_start(ap, format);
	buf.str = NULL;
	buf.size = 0;
	expand_buf(&buf);
	ret = fill_buf(&buf, format, ap);
	va_end(ap);
	if (ret != 0)
		ret = write(1, buf.str, ret);
	if (buf.str != NULL)
		free(buf.str);
	return (ret);
}
