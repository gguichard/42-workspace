/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:34:49 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/25 16:54:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

char	f_type(mode_t st_mode)
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

char	f_perm(mode_t mode, int perm)
{
	if (perm == 4 && mode & 4)
		return ('r');
	if (perm == 2 && mode & 2)
		return ('w');
	if (perm == 1 && mode & 1)
		return ('x');
	return ('-');
}
