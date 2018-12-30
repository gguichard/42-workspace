/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 21:21:38 by gguichar         ###   ########.fr       */
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

int	key_hook(int keycode, t_fdf *fdf)
{
	int	ret;

	ret = 0;
	if (keycode == 53)
		exit_fdf(fdf);
	else if (keycode == 69 || keycode == 78)
		ret = handle_scale(fdf, keycode);
	else if (keycode == 116 || keycode == 121)
		ret = handle_depth(fdf, keycode);
	else if (keycode == 123 || keycode == 124)
		ret = handle_angle(fdf, keycode);
	else if (keycode == 34 || keycode == 35)
		ret = handle_proj(fdf, keycode);
	if (ret)
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}
