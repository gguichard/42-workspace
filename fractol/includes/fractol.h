/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/03 19:40:09 by gguichar         ###   ########.fr       */
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
# include "opencl.h"

# define FRACT_MAX_THREADS 4
# define FRACT_PREVIEWS 4
# define FRACT_PREVIEWS_MAXITERS 50
# define FRACT_PREVIEWS_WIDTH 256
# define FRACT_PREVIEWS_HEIGHT 158
# define FRACT_PREVIEWS_COLOR 0xFFFFFF

typedef enum e_type		t_type;
typedef struct s_data	t_data;
typedef struct s_thread	t_thread;
typedef struct s_point	t_point;

enum	e_type
{
	NO_FRACT = 0,
	JULIA,
	JULIA3,
	MANDELBROT,
	MANDELBROT3,
	MANDELBAR,
	BURNING_SHIP
};

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
	t_type			fract_type;
	int				(*fract_fn)(t_motion *, double, double, int);
	void			(*draw_fn)(t_data *);
	int				not_epileptic;
	int				color_mul;
	int				max_iters;
	t_keys			keys;
	t_motion		motion;
	int				sampling;
	int				preview_idx;
	t_mlximg		previews[FRACT_PREVIEWS];
	t_thread		threads[FRACT_MAX_THREADS];
	int				network_sock;
	int				use_opencl;
	t_cl			cl;
};

struct	s_point
{
	double	x;
	double	y;
};

int		init_mlx(t_mlx *lib, t_winsize *ws);
int		setup_fractal_type(t_data *data, int argc, char **argv);

void	*get_preview_draw_fn(int idx);
void	draw_selected_preview(t_data *data);
void	draw_preview(t_data *data, t_mlximg *img
		, int (*fract_fn)(t_motion *, double, double, int));
void	destroy_previews(t_data *data);
int		init_previews(t_data *data);

void	redraw_all(t_data *data);
void	reset_draw(t_data *data);
void	change_fract_type(t_data *data, int idx);
void	increase_sampling(t_data *data);

int		exit_lib(t_data *data);
int		loop_hook(t_data *data);
int		keypress_hook(int keycode, t_data *data);
int		keyrelease_hook(int keycode, t_data *data);
int		motion_hook(int x, int y, t_data *data);
int		expose_hook(t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);

void	init_thread_values(t_data *data);
int		setup_opencl(t_data *data);
void	release_opencl(t_data *data);
int		setup_network(t_data *data);

void	draw_threads(t_data *data);
void	draw_gpu(t_data *data);
void	draw_network(t_data *data);

int		fract_bailout(t_point point, double re, double im, int max_iters);
int		fract_bailout_2(t_point point, double re, double im, int max_iters);
int		fract_inv_bailout(t_point point, double re, double im, int max_iters);

int		julia(t_motion *motion, double re, double im, int max_iters);
int		mandelbrot(t_motion *motion, double re, double im, int max_iters);
int		mandelbar(t_motion *motion, double re, double im, int max_iters);
int		burning_ship(t_motion *motion, double re, double im, int max_iters);

int		get_fract_color(int iters);

#endif
