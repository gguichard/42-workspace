/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:25:24 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/26 23:23:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"

long	opt_mask(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1 << (c - 'a'));
	else if (c >= 'A' && c <= 'Z')
		return ((long)1 << (c - 'A') << 26);
	else if (c >= '0' && c <= '9')
		return ((long)1 << (c - '0') << 52);
	return (0);
}

void	file_error(const char *file)
{
	ft_dprintf(2, "ft_ls: %s: %s\n", file, strerror(errno));
}

void	exit_error(const char *err)
{
	ft_dprintf(2, "ft_ls: %s\n", err);
	exit(1);
}

char	*get_path(const char *dir, const char *file)
{
	char	*str;

	if (file == NULL)
		return (ft_strdup(dir));
	ft_asprintf(&str, "%s/%s", ft_strcmp(dir, "/") == 0 ? "" : dir, file);
	return (str);
}
