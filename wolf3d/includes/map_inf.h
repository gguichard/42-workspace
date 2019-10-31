/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:16:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/31 09:16:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_INF_H
# define MAP_INF_H

# include <string.h>
# include "tile_inf.h"
# include "player.h"

typedef struct	s_map_inf
{
	int			width;
	int			height;
	t_tile_id	*tiles;
	t_player	player;
	int			has_player;
}				t_map_inf;

#endif
