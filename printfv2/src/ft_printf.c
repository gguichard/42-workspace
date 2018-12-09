/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 20:39:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/09 23:28:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"

int	ft_printf(const char *format, ...)
{
	t_pf	pf;

	pf.fd = 1;
	pf.buf_off = 0;
	pf.buf_write = 0;
	va_start(pf.ap, format);
	pf_parse(&pf, format);
	va_end(pf.ap);
	pf.buf_write += write(pf.fd, pf.buf, pf.buf_off);
	return (pf.buf_write);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_pf	pf;

	pf.fd = fd;
	pf.buf_off = 0;
	pf.buf_write = 0;
	va_start(pf.ap, format);
	pf_parse(&pf, format);
	va_end(pf.ap);
	pf.buf_write += write(pf.fd, pf.buf, pf.buf_off);
	return (pf.buf_write);
}
