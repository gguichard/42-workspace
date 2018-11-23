/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 15:41:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	ret = fill_buf(&buf, format, ap);
	va_end(ap);
	if (ret > 0)
		ret = write(1, buf.str, buf.offset);
	if (buf.str != NULL)
		free(buf.str);
	return (ret);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	if (fd < 0 || format == NULL)
		return (-1);
	va_start(ap, format);
	ret = fill_buf(&buf, format, ap);
	va_end(ap);
	if (ret > 0)
		ret = write(fd, buf.str, buf.offset);
	if (buf.str != NULL)
		free(buf.str);
	return (ret);
}

int			ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	if (str == NULL || format == NULL)
		return (-1);
	va_start(ap, format);
	ret = fill_buf(&buf, format, ap);
	va_end(ap);
	if (ret > 0)
	{
		ft_memcpy(str, buf.str, buf.offset);
		str[buf.offset] = '\0';
	}
	if (buf.str != NULL)
		free(buf.str);
	return (ret);
}

int			ft_asprintf(char **ret, const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		iret;

	if (ret == NULL || format == NULL)
		return (-1);
	va_start(ap, format);
	iret = fill_buf(&buf, format, ap);
	va_end(ap);
	if (iret > 0)
	{
		if (!(*ret = (char *)malloc(buf.offset + 1)))
			exit(1);
		ft_memcpy(*ret, buf.str, buf.offset);
		(*ret)[buf.offset] = '\0';
	}
	if (buf.str != NULL)
		free(buf.str);
	return (iret);
}
