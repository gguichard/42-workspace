/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 23:26:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/04 15:44:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

typedef struct s_netdata	t_netdata;

struct	s_netdata
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
	int		sampling;
};

#endif
