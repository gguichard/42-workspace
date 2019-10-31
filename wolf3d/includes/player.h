/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:20:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/31 13:52:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vec2.h"

typedef struct	s_player
{
	t_vec2d		position;
	t_vec2d		dir;
	t_vec2d		vel;
	double		angle;
	double		fov;
	double		dist_to_proj;
}				t_player;

#endif
