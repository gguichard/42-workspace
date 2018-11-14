/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 16:54:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*pad_string(char *str, char padding, size_t total)
{
	size_t	len;
	char	*ret;

	ret = str;
	len = ft_strlen(str);
	if (total > len)
	{
		if (!(ret = (char *)malloc(total + 1)))
			return (NULL);
		ft_memset(ret, padding, total - len);
		ft_memcpy(ret + (total - len), str, len + 1);
	}
	free(str);
	return (ret);
}
