/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:58:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/15 15:07:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "mlx_opengl.h"
#include "winsize.h"
#include "lib_mlx.h"

void	clean_mlx(t_mlx *lib)
{
	if (lib->win_ptr != NULL)
	{
		mlx_destroy_window(lib->mlx_ptr, lib->win_ptr);
		lib->win_ptr = NULL;
	}
	if (lib->img_ptr != NULL)
	{
		mlx_destroy_image(lib->mlx_ptr, lib->img_ptr);
		lib->img_ptr = NULL;
	}
}

int		init_mlx(t_mlx *lib, t_winsize winsize, char *win_title)
{
	if (!(lib->mlx_ptr = mlx_init()))
		return (0);
	lib->win_ptr = mlx_new_opengl_window(lib->mlx_ptr
			, winsize.width, winsize.height
			, win_title);
	if (!(lib->win_ptr))
		return (0);
	lib->img_ptr = mlx_new_image(lib->mlx_ptr
			, winsize.width, winsize.height);
	if (!(lib->img_ptr))
		return (0);
	lib->img_data = (unsigned int *)mlx_get_data_addr(lib->img_ptr
			, &(lib->bits_per_pixel)
			, &(lib->size_line)
			, &(lib->endian));
	if (!(lib->img_data))
		return (0);
	return (1);
}
