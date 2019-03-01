/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:46:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/01 22:40:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define OPENCL_SOURCE 8192

typedef struct s_data	t_data;

struct	s_data
{
	int		type;
	int		width;
	int		height;
	int		x_off;
	int		y_off;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	motion_x;
	double	motion_y;
	int		max_iters;
};

char	*read_sourcecode(void);
void	compute_fractal(t_data *data, const char *source, int *buffer);
int		*rle_compress(int *buffer, int size, int *new_size);

#endif
