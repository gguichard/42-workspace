/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_inf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:20:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 21:22:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_INF_H
# define PLAYER_INF_H

# include "vec2.h"

typedef struct	s_player_inf
{
	t_vec2d		position;
	double		angle;
}				t_player_inf;

#endif
