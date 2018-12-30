/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/30 06:13:18 by gguichar         ###   ########.fr       */
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
	ft_asprintf(&str, "Scale factor: %d | Depth factor: %d"
			, fdf->scale, fdf->depth);
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
	if (keycode == 53)
		exit_fdf(fdf);
	else if (keycode == 69)
		(fdf->scale) += 2;
	else if (keycode == 78)
		(fdf->scale) -= 2;
	else if (keycode == 116)
		(fdf->depth) += 1;
	else if (keycode == 121)
		(fdf->depth) -= 1;
	if (keycode == 69 || keycode == 78 || keycode == 116 || keycode == 121)
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}
