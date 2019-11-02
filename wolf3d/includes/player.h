/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:20:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/02 19:06:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vec2.h"

# define PLAYER_ACCEL 0.025
# define PLAYER_STRAFE_ACCEL 0.015
# define PLAYER_MAX_SPEED 0.1
# define PLAYER_VELOCITY_DECREASE 0.8
# define PLAYER_HALF_SIZE 0.25

typedef struct	s_player
{
	t_vec2d		position;
	t_vec2d		velocity;
	double		angle;
	double		fov;
	double		dist_to_proj;
}				t_player;

#endif
