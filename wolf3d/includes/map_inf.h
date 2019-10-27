/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:16:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 22:51:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_INF_H
# define MAP_INF_H

# include <string.h>
# include "tile_inf.h"
# include "player_inf.h"

typedef struct	s_map_inf
{
	size_t			width;
	size_t			height;
	t_tile_id		*tiles;
	t_player_inf	player;
	int				has_player;
}				t_map_inf;

#endif
