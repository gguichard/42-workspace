/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:55:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/20 22:50:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <SDL.h>
# include <stdint.h>
# include "window.h"
# include "keystates.h"
# include "map_inf.h"
# include "tile_inf.h"
# include "player.h"
# include "ray_inf.h"
# include "texture_inf.h"
# include "minimap_inf.h"
# include "vec2.h"
# include "error.h"

# define CEIL_COLOR 0x303030
# define FLOOR_COLOR 0x505050

# define MINIMAP_SIZE 0.2
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define MINIMAP_VIEW_RADIUS 10
# define MINIMAP_BORDER 1
# define MINIMAP_BORDER_COLOR 0xFFFFFF
# define MINIMAP_PLAYER_COLOR 0xFFFFFF
# define MINIMAP_RAY_COLOR 0xF4A142
# define MINIMAP_WALL_COLOR 0x000000
# define MINIMAP_OUTSIDE_COLOR 0x000000

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
	t_map_inf		tile_map;
	t_minimap_inf	minimap;
	t_player		player;
	t_texture_inf	textures[4];
}				t_ctx;

typedef void	t_statefn(t_ctx *ctx);
typedef int		t_state_evtfn(t_ctx *ctx, SDL_Event evt);

void			place_player_map(t_map_inf *map_inf, t_tile_inf *tile_inf);
t_map_inf		load_mapfile(const char *file, t_error *err);
t_error			load_texture(const char *file, t_texture_inf *text_inf);

t_error			wolf3d_init(t_ctx *ctx, const char *mapfile);
void			wolf3d_run(t_ctx *ctx);
void			wolf3d_clean(t_ctx *ctx);

void			wolf3d_main_menu(t_ctx *ctx);
void			wolf3d_play(t_ctx *ctx);
int				wolf3d_play_events(t_ctx *ctx, SDL_Event event);

void			player_view_raycast(t_ctx *ctx);

t_ray_inf		launch_ray(t_vec2d origin, double angle, t_map_inf *map_inf);
void			check_collision_after_move(t_ctx *ctx, t_vec2d old_position);

t_error			minimap_setup(t_ctx *ctx);
void			minimap_destroy(t_minimap_inf *minimap);
void			minimap_reset_z_buffer(t_ctx *ctx);
void			minimap_background(t_ctx *ctx);
void			minimap_ray(t_ctx *ctx, double length, double angle);
void			draw_minimap_view(t_ctx *ctx);

t_ray_inf		launch_portal_ray(t_ray_inf hit_inf, double angle
	, t_map_inf *map_inf, int depth);
void			teleport_through_portal(t_ctx *ctx, t_tile_meta *tile);

#endif
