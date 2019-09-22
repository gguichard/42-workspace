/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 21:30:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 15:12:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"
#include "vectors.h"

static const t_key	g_keys[] = {
	{KEY_A, TRANSLATE_X_LEFT}, {KEY_D, TRANSLATE_X_RIGHT},
	{KEY_W, TRANSLATE_Y_UP}, {KEY_S, TRANSLATE_Y_DOWN},
	{KEY_MINUS, SCALE_OUT}, {KEY_PLUS, SCALE_IN},
	{KEY_PAGE_UP, DEPTH_INCREASE}, {KEY_ARROW_UP, DEPTH_INCREASE},
	{KEY_PAGE_DOWN, DEPTH_DECREASE}, {KEY_ARROW_DOWN, DEPTH_DECREASE},
	{KEY_ARROW_LEFT, ROTATE_LEFT}, {KEY_ARROW_RIGHT, ROTATE_RIGHT}
};

int	keypress_hook(int keycode, t_fdf *fdf)
{
	size_t	idx;

	if (keycode == KEY_R)
	{
		fdf->keys ^= ENABLE_RASTERIZATION;
		fill_window_image(fdf);
		expose_hook(fdf);
	}
	else
	{
		idx = 0;
		while (idx < (sizeof(g_keys) / sizeof(g_keys[0])))
		{
			if (keycode == g_keys[idx].keycode)
				fdf->keys |= g_keys[idx].bitmask;
			idx++;
		}
	}
	return (0);
}

int	keyrelease_hook(int keycode, t_fdf *fdf)
{
	size_t	idx;

	if (keycode == KEY_ESCAPE)
		exit_fdf(fdf);
	else
	{
		idx = 0;
		while (idx < (sizeof(g_keys) / sizeof(g_keys[0])))
		{
			if (keycode == g_keys[idx].keycode)
				fdf->keys &= ~g_keys[idx].bitmask;
			idx++;
		}
	}
	return (0);
}

int	button_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == KEY_MOUSE_LEFT)
	{
		fdf->drag = !fdf->drag;
		fdf->prev_cursor = vec2d(x, y);
	}
	return (0);
}
