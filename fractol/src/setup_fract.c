/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:36:27 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/04 13:05:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static void	setup_fract3_types(t_data *data, const char *name)
{
	int	ret3;

	ret3 = 0;
	if (ft_strequ("Custombrot", name))
	{
		data->fract_fn = mandelbrot;
		data->fract_type = CUSTOMBROT;
	}
	else if (ft_strequ("Mandelbrot", name)
			|| (ret3 = ft_strequ("Mandelbrot3", name)))
	{
		data->fract_fn = mandelbrot;
		data->fract_type = ret3 ? MANDELBROT3 : MANDELBROT;
	}
	else if (ft_strequ("Julia", name)
			|| (ret3 = ft_strequ("Julia3", name)))
	{
		data->fract_fn = julia;
		data->fract_type = ret3 ? JULIA3 : JULIA;
		data->motion.record = 1;
	}
}

int			setup_fractal_type(t_data *data, int argc, char **argv)
{
	if (data->opts->index < argc)
	{
		if (ft_strequ("Tricorn", argv[data->opts->index]))
		{
			data->fract_fn = mandelbar;
			data->fract_type = MANDELBAR;
		}
		else if (ft_strequ("BurningShip", argv[data->opts->index]))
		{
			data->fract_fn = burning_ship;
			data->fract_type = BURNING_SHIP;
		}
		else
			setup_fract3_types(data, argv[data->opts->index]);
	}
	return (data->fract_type != NO_FRACT);
}
