/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/01 04:12:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "printf.h"
#include "fdf.h"

int	expose_hook(t_fdf *fdf)
{
	char	*str;

	mlx_put_image_to_window(fdf->lib.mlx_ptr
			, fdf->lib.win_ptr
			, fdf->lib.img_ptr
			, 0, 0);
	ft_asprintf(&str
			, "%s: %d | %s: %d | %s: %ddeg | %s: %s | Press %c to change"
			, "Scale", fdf->scale
			, "Depth", fdf->depth
			, "Angle", fdf->angle
			, "Projection", fdf->proj == ISO ? "Isometric" : "Parallel"
			, fdf->proj == ISO ? 'P' : 'I');
	if (str != NULL)
	{
		mlx_string_put(fdf->lib.mlx_ptr
				, fdf->lib.win_ptr, 50, fdf->height - 50, 0xFFFFFF, str);
		free(str);
	}
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	if (handle_move(fdf) || handle_scale(fdf)
			|| handle_depth(fdf) || handle_angle(fdf))
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}

int	keypress_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 0 || keycode == 2)
		fdf->move.x = (keycode == 2) ? -10 : 10;
	else if (keycode == 1 || keycode == 13)
		fdf->move.y = (keycode == 1) ? -10 : 10;
	else if (keycode == 24 || keycode == 27)
		fdf->move.scale = (keycode == 27) ? -1 : 1;
	else if (keycode == 116 || keycode == 121)
		fdf->move.depth = (keycode == 121) ? -1 : 1;
	else if (keycode == 123 || keycode == 124)
		fdf->move.angle = (keycode == 123) ? -15 : 15;
	return (0);
}

int	keyrelease_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		exit_fdf(fdf);
	else if (keycode == 0 || keycode == 2)
		fdf->move.x = 0;
	else if (keycode == 1 || keycode == 13)
		fdf->move.y = 0;
	else if (keycode == 24 || keycode == 27)
		fdf->move.scale = 0;
	else if (keycode == 116 || keycode == 121)
		fdf->move.depth = 0;
	else if (keycode == 123 || keycode == 124)
		fdf->move.angle = 0;
	else if (keycode == 34 || keycode == 35)
	{
		if (handle_proj(fdf, keycode))
		{
			fill_window_image(fdf);
			expose_hook(fdf);
		}
	}
	return (0);
}
