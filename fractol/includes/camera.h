/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 02:24:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/21 22:49:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_camera
{
	int			x_off;
	int			y_off;
	double		scale;
	double		x_min;
	double		y_min;
	double		x_max;
	double		y_max;
}				t_camera;

#endif
