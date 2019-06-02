/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 21:30:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 21:31:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"
#include "vectors.h"

int	keypress_hook(int keycode, t_fdf *fdf)
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
	else if (keycode == KEY_PAGE_UP || keycode == KEY_ARROW_UP)
		fdf->keys |= DEPTH_INCREASE;
	else if (keycode == KEY_PAGE_DOWN || keycode == KEY_ARROW_DOWN)
		fdf->keys |= DEPTH_DECREASE;
	else if (keycode == KEY_ARROW_LEFT)
		fdf->keys |= ROTATE_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		fdf->keys |= ROTATE_RIGHT;
	return (0);
}

int	keyrelease_hook(int keycode, t_fdf *fdf)
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
	else if (keycode == KEY_PAGE_UP || keycode == KEY_ARROW_UP)
		fdf->keys &= ~DEPTH_INCREASE;
	else if (keycode == KEY_PAGE_DOWN || keycode == KEY_ARROW_DOWN)
		fdf->keys &= ~DEPTH_DECREASE;
	else if (keycode == KEY_ARROW_LEFT)
		fdf->keys &= ~ROTATE_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		fdf->keys &= ~ROTATE_RIGHT;
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
