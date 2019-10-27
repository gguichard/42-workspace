/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:55:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:08:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdint.h>
# include "window.h"
# include "keystates.h"
# include "map_inf.h"
# include "player_inf.h"
# include "error.h"

typedef enum	e_state
{
	MAIN_MENU = 0,
	PLAYING = 1,
	OPTIONS = 2,
	QUIT = 3,
	STATE_LAST = 4
}				t_state;

typedef struct	s_ctx
{
	t_win_data		window;
	t_state			state;
	uint64_t		keystates;
	uint32_t		*pixels;
	t_map_inf		tile_map;
	t_player_inf	player;
}				t_ctx;

typedef void t_statefn(t_ctx *ctx);

void			place_player_map(t_map_inf *map_inf, t_tile_inf *tile_inf);
t_map_inf		load_mapfile(const char *file, t_error *err);

t_error			wolf3d_init(const char *mapfile);
void			wolf3d_run(t_ctx *ctx);

void			wolf3d_main_menu(t_ctx *ctx);
void			wolf3d_play(t_ctx *ctx);

#endif
