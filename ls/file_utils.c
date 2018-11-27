/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:34:49 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/27 09:30:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

char	file_type(mode_t st_mode)
{
	if (S_ISBLK(st_mode))
		return ('b');
	if (S_ISCHR(st_mode))
		return ('c');
	if (S_ISDIR(st_mode))
		return ('d');
	if (S_ISLNK(st_mode))
		return ('l');
	if (S_ISSOCK(st_mode))
		return ('s');
	if (S_ISFIFO(st_mode))
		return ('p');
	return ('-');
}

char	*file_permissions(mode_t mode, int shift)
{
	static char	out[3][4];
	static int	index = -1;

	index++;
	if (index == 3)
		index = 0;
	out[index][3] = '\0';
	out[index][0] = ((mode >> shift) & 4) ? 'r' : '-';
	out[index][1] = ((mode >> shift) & 2) ? 'w' : '-';
	out[index][2] = ((mode >> shift) & 1) ? 'x' : '-';
	if ((shift == 6 && mode & S_ISUID) || (shift == 3 && mode & S_ISGID))
		out[index][2] = !((mode >> shift) & 1) ? 'S' : 's';
	return (out[index]);
}
