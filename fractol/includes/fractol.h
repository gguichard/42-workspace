/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/02 11:57:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "lib.h"
# include "winsize.h"
# include "options.h"

enum				e_fract
{
	FRACT_JULIA,
	FRACT_MANDELBROT
};

typedef struct		s_data
{
	t_mlx			lib;
	t_opts			*opts;
	t_winsize		winsize;
	enum e_fract	fractal;
}					t_data;

int					init_mlx(t_mlx *lib, t_winsize *ws);
int					exit_lib(t_data *data);

#endif