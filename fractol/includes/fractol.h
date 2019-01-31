/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/31 10:53:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_WIDTH 1640
# define WIN_HEIGHT 1280

# include "mlx.h"

typedef enum	e_type
{
	JULIA,
	MANDELBROT
}				t_type;

typedef struct	s_fractol
{
	t_mlx		lib;
	t_opts		*opts;
	
}				t_fractol;

#endif
