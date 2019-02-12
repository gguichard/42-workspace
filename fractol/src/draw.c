/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:47:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 07:27:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "libft.h"
#include "fractol.h"

int			get_fract_color(int iters)
{
	static int	colors[] = {
		0x421e0f, 0x19071a, 0x09012f, 0x040449,
		0x000764, 0x022c8a, 0x1852b1, 0x397dd1,
		0x86b5e5, 0xd3ecf8, 0xf1e9bf, 0xf8c95f,
		0xffaa00, 0xcc8000, 0x995700, 0x6a3403
	};

	return (colors[iters % 16]);
}

void		init_thread_values(t_data *data)
{
	int			idx;
	int			cols_per_thread;
	t_thread	*thread;

	idx = 0;
	cols_per_thread = data->winsize.width / FRACT_MAX_THREADS;
	while (idx < FRACT_MAX_THREADS)
	{
		thread = &data->threads[idx];
		thread->data = data;
		thread->x = cols_per_thread * idx;
		thread->y = 0;
		if (idx + 1 == FRACT_MAX_THREADS)
			thread->width = data->winsize.width;
		else
			thread->width = thread->x + cols_per_thread;
		thread->height = data->winsize.height;
		idx++;
	}
	data->draw_fn = draw_threads;
}

static void	*threaded_draw(t_thread *thread)
{
	int		x;
	int		y;
	double	re;
	double	im;
	int		iters;

	x = thread->x;
	while (x < thread->width)
	{
		y = thread->y;
		while (y < thread->height)
		{
			re = x * (thread->data->cam.x_max - thread->data->cam.x_min)
				/ thread->data->winsize.width + thread->data->cam.x_min;
			im = y * (thread->data->cam.y_max - thread->data->cam.y_min)
				/ thread->data->winsize.height + thread->data->cam.y_min;
			iters = thread->data->fract_fn(&thread->data->motion, re, im
					, thread->data->max_iters);
			thread->data->lib.img_data[y * thread->data->winsize.width + x] =
				iters < thread->data->max_iters ? get_fract_color(iters) : 0;
			y++;
		}
		x++;
	}
	return (NULL);
}

void		draw_threads(t_data *data)
{
	int			idx;
	t_thread	*thread;

	idx = 0;
	while (idx < FRACT_MAX_THREADS)
	{
		thread = &data->threads[idx];
		pthread_create(&thread->id, NULL, (void *)threaded_draw, thread);
		idx++;
	}
	idx = 0;
	while (idx < FRACT_MAX_THREADS)
	{
		pthread_join(data->threads[idx].id, NULL);
		idx++;
	}
}
