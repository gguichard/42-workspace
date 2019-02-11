/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/11 07:38:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <pthread.h>
# include "lib.h"
# include "winsize.h"
# include "options.h"
# include "camera.h"
# include "keys.h"
# include "motion.h"

# define FRACT_MAX_THREADS 4

typedef struct s_data	t_data;
typedef struct s_thread	t_thread;

struct	s_thread
{
	pthread_t	id;
	int			x;
	int			y;
	int			width;
	int			height;
	t_data		*data;
};

struct	s_data
{
	t_mlx			lib;
	t_opts			*opts;
	t_winsize		winsize;
	t_camera		cam;
	int				(*fract_fn)(t_motion *, double, double, int);
	void			(*draw_fn)(t_data *);
	int				max_iters;
	t_keys			keys;
	t_motion		motion;
	t_thread		threads[FRACT_MAX_THREADS];
};

int		init_mlx(t_mlx *lib, t_winsize *ws);

int		exit_lib(t_data *data);
int		loop_hook(t_data *data);
int		keypress_hook(int keycode, t_data *data);
int		keyrelease_hook(int keycode, t_data *data);
int		motion_hook(int x, int y, t_data *data);
int		expose_hook(t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);

void	draw_gpu(t_data *data);
void	draw_threads(t_data *data);

int		julia(t_motion *motion, double re, double im, int max_iters);
int		mandelbrot(t_motion *motion, double re, double im, int max_iters);
int		mandelbar(t_motion *motion, double re, double im, int max_iters);

#endif
