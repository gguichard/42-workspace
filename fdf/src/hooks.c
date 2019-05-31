/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 04:05:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/31 19:40:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "printf.h"
#include "fdf.h"
#include "keys.h"

int			expose_hook(t_fdf *fdf)
{
	char	*str;

	mlx_put_image_to_window(fdf->lib.mlx_ptr
		, fdf->lib.win_ptr
		, fdf->lib.img_ptr
		, 0, 0);
	ft_asprintf(&str, "Projection: %s | Press %c to change"
		, fdf->proj == ISO ? "Isometric" : "Parallel"
		, fdf->proj == ISO ? 'P' : 'I');
	if (str != NULL)
	{
		mlx_string_put(fdf->lib.mlx_ptr
			, fdf->lib.win_ptr, 50, fdf->winsize.height - 50, 0xFFFFFF, str);
		free(str);
	}
	return (0);
}

int			loop_hook(t_fdf *fdf)
{
	int	ret;

	ret = 0;
	if (handle_move(fdf))
		ret = 1;
	if (handle_scale(fdf))
		ret = 1;
	if (handle_depth(fdf))
		ret = 1;
	if (handle_angle(fdf))
		ret = 1;
	if (ret)
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	return (0);
}

int			keypress_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_A)
		fdf->keys |= TRANSLATE_X_LEFT;
	else if (keycode == KEY_D)
		fdf->keys |= TRANSLATE_X_RIGHT;
	else if (keycode == KEY_W)
		fdf->keys |= TRANSLATE_Y_UP;
	else if (keycode == KEY_S)
		fdf->keys |= TRANSLATE_Y_DOWN;
	else if (keycode == KEY_MINUS)
		fdf->keys |= SCALE_OUT;
	else if (keycode == KEY_PLUS)
		fdf->keys |= SCALE_IN;
	else if (keycode == KEY_PAGE_UP)
		fdf->keys |= DEPTH_INCREASE;
	else if (keycode == KEY_PAGE_DOWN)
		fdf->keys |= DEPTH_DECREASE;
	else if (keycode == KEY_LEFT_ARROW)
		fdf->keys |= ROTATE_LEFT;
	else if (keycode == KEY_RIGHT_ARROW)
		fdf->keys |= ROTATE_RIGHT;
	return (0);
}

static void	keyrelease_hook_proj(int keycode, t_fdf *fdf)
{
	if (handle_proj(fdf, keycode))
	{
		fill_window_image(fdf);
		expose_hook(fdf);
	}
}

int			keyrelease_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESCAPE)
		exit_fdf(fdf);
	else if (keycode == KEY_A)
		fdf->keys &= ~TRANSLATE_X_LEFT;
	else if (keycode == KEY_D)
		fdf->keys &= ~TRANSLATE_X_RIGHT;
	else if (keycode == KEY_W)
		fdf->keys &= ~TRANSLATE_Y_UP;
	else if (keycode == KEY_S)
		fdf->keys &= ~TRANSLATE_Y_DOWN;
	else if (keycode == KEY_MINUS)
		fdf->keys &= ~SCALE_OUT;
	else if (keycode == KEY_PLUS)
		fdf->keys &= ~SCALE_IN;
	else if (keycode == KEY_PAGE_UP)
		fdf->keys &= ~DEPTH_INCREASE;
	else if (keycode == KEY_PAGE_DOWN)
		fdf->keys &= ~DEPTH_DECREASE;
	else if (keycode == KEY_LEFT_ARROW)
		fdf->keys &= ~ROTATE_LEFT;
	else if (keycode == KEY_RIGHT_ARROW)
		fdf->keys &= ~ROTATE_RIGHT;
	else if (keycode == KEY_I || keycode == KEY_P)
		keyrelease_hook_proj(keycode, fdf);
	return (0);
}
