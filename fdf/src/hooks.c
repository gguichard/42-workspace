/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 11:42:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "printf.h"
#include "fdf.h"

int			expose_hook(t_fdf *fdf)
{
	char	*str;

	mlx_put_image_to_window(fdf->lib.mlx_ptr
			, fdf->lib.win_ptr
			, fdf->lib.img_ptr
			, 0, 0);
	ft_asprintf(&str
			, "Scale: %d | Depth: %d | Projection: %s | Press %c to change"
			, fdf->scale
			, fdf->depth
			, fdf->proj == ISO ? "Isometric" : "Parallel"
			, fdf->proj == ISO ? 'P' : 'I');
	if (str != NULL)
	{
		mlx_string_put(fdf->lib.mlx_ptr
				, fdf->lib.win_ptr, 50, fdf->height - 50, 0xFFFFFF, str);
		free(str);
	}
	return (0);
}

static int	handle_scale(t_fdf *fdf, int keycode)
{
	if (keycode == 69)
		(fdf->scale) += 1;
	else if (keycode == 78)
	{
		if (fdf->scale - 1 <= 0)
			return (0);
		(fdf->scale) -= 1;
	}
	return (1);
}

static int	handle_depth(t_fdf *fdf, int keycode)
{
	if (keycode == 116)
		(fdf->depth) += 1;
	else if (keycode == 121)
		(fdf->depth) -= 1;
	return (1);
}

static int	handle_proj(t_fdf *fdf, int keycode)
{
	if (keycode == 34)
	{
		fdf->proj = ISO;
		fdf->f_proj = &iso;
	}
	else if (keycode == 35)
	{
		fdf->proj = PARALLEL;
		fdf->f_proj = &parallel;
	}
	return (1);
}

int			key_hook(int keycode, t_fdf *fdf)
{
	int	ret;

	ret = 0;
	if (keycode == 53)
		exit_fdf(fdf);
	else if (keycode == 69 || keycode == 78)
		ret = handle_scale(fdf, keycode);
	else if (keycode == 116 || keycode == 121)
		ret = handle_depth(fdf, keycode);
	else if (keycode == 34 || keycode == 35)
		ret = handle_proj(fdf, keycode);
	if (ret)
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}
