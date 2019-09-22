/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:03:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/22 15:20:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "fdf.h"

static void	clear_window(t_fdf *fdf)
{
	int	index;
	int	total;

	index = 0;
	total = fdf->winsize.width * fdf->winsize.height;
	while (index < total)
	{
		(fdf->z_buffer)[index] = INT_MIN;
		index++;
	}
	ft_memset(fdf->lib.img_data, 0, fdf->lib.size_line * fdf->winsize.height);
}

void		fill_window_image(t_fdf *fdf)
{
	clear_window(fdf);
	fdf->draw_window_fn(fdf);
}
