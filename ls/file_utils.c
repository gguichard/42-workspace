/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:34:49 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/24 12:06:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	f_type(mode_t st_mode)
{
	if (st_mode & S_IFIFO)
		return ('p');
	if (st_mode & S_IFCHR)
		return ('c');
	if (st_mode & S_IFDIR)
		return ('d');
	if (st_mode & S_IFBLK)
		return ('b');
	if (st_mode & S_IFREG)
		return ('-');
	if (st_mode & S_IFLNK)
		return ('l');
	if (st_mode & S_IFSOCK)
		return ('s');
	return ('?');
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
