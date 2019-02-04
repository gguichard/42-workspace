/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:27:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/31 11:54:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "lib.h"
#include "winsize.h"

int		init_mlx(t_mlx *lib, t_winsize *ws)
{
	if ((lib->mlx_ptr = mlx_init()) == NULL)
		return (0);
	lib->win_ptr = mlx_new_window(lib->mlx_ptr, ws->width, ws->height
			, "Frac'ol");
	if (lib->win_ptr == NULL)
		return (0);
	lib->img_ptr = mlx_new_image(lib->mlx_ptr, ws->width, ws->height);
	if (lib->img_ptr == NULL)
		return (0);
	lib->img_data = (unsigned int *)mlx_get_data_addr(lib->img_ptr
			, &(lib->bits_per_pixel), &(lib->size_line), &(lib->endian));
	if (lib->img_data == NULL)
		return (0);
	return (1);
}

void	destroy_mlx(t_mlx *lib)
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
