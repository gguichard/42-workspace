/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/31 02:20:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "printf.h"
#include "fdf.h"

int	loop_hook(t_fdf *fdf)
{
	if (handle_scale(fdf) || handle_depth(fdf) || handle_angle(fdf))
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}

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

int	keypress_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 69 || keycode == 78)
		fdf->move.scale = (keycode == 78) ? -1 : 1;
	else if (keycode == 116 || keycode == 121)
		fdf->move.depth = (keycode == 121) ? -1 : 1;
	else if (keycode == 123 || keycode == 124)
		fdf->move.angle = (keycode == 123) ? -15 : 15;
	return (0);
}

int	keyrelease_hook(int keycode, t_fdf *fdf)
{
	int	ret;

	ret = 0;
	if (keycode == 53)
		exit_fdf(fdf);
	else if (keycode == 69 || keycode == 78)
		fdf->move.scale = 0;
	else if (keycode == 116 || keycode == 121)
		fdf->move.depth = 0;
	else if (keycode == 123 || keycode == 124)
		fdf->move.angle = 0;
	else if (keycode == 34 || keycode == 35)
		ret = handle_proj(fdf, keycode);
	if (ret)
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}
