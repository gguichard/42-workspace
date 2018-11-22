/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:29:01 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 13:33:07 by gguichar         ###   ########.fr       */
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
