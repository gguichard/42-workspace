/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:35:37 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/22 10:51:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

int	utf8_valid(wint_t c)
{
	if (c < (1 << 7))
		return (1);
	else if (c < (1 << 11) && MB_CUR_MAX < 2)
		return (0);
	else if (c < (1 << 16) && MB_CUR_MAX < 3)
		return (0);
	else if (c < (1 << 21) && MB_CUR_MAX < 4)
		return (0);
	else if (c >= (1 << 21))
		return (0);
	return (1);
}

int	convert_utf8(char *dst, wint_t c)
{
	int	index;

	index = 0;
	if (c < (1 << 7))
		dst[index++] = c;
	else if (c < (1 << 11))
	{
		dst[index++] = (c >> 6) | 0xC0;
		dst[index++] = (c & 0x3F) | 0x80;
	}
	else if (c < (1 << 16))
	{
		dst[index++] = (c >> 12) | 0xE0;
		dst[index++] = ((c >> 6) & 0x3F) | 0x80;
		dst[index++] = (c & 0x3F) | 0x80;
	}
	else if (c < (1 << 21))
	{
		dst[index++] = (c >> 18) | 0xF0;
		dst[index++] = ((c >> 12) & 0x3F) | 0x80;
		dst[index++] = ((c >> 6) & 0x3F) | 0x80;
		dst[index++] = (c & 0x3F) | 0x80;
	}
	return (index);
}

int	convert_utf8_str(char *dst, wchar_t *str)
{
	int	offset;

	offset = 0;
	while (*str != L'\0')
	{
		offset += convert_utf8(&(dst[offset]), *str);
		if (!utf8_valid(*str))
			return (0);
		str++;
	}
	return (1);
}
