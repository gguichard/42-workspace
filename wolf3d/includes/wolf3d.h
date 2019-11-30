/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:55:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 17:55:43 by gguichar         ###   ########.fr       */
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
# include "thread_inf.h"
# include "column_inf.h"
# include "vec2.h"
# include "error.h"

# define THREADS_COUNT 4

# define CEIL_COLOR 0xff303030
# define FLOOR_COLOR 0xff505050

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
# define FOG_DIST 15

# define ALPHA_CHANNEL 0xff000000

# define PORTAL_ENTRY_TEXTURE 4
# define PORTAL_EXIT_TEXTURE 5

typedef enum	e_state_type
{
	MAIN_MENU = 0,
	PLAYING = 1,
	OPTIONS = 2,
	QUIT = 3,
	STATE_LAST = 4
}				t_state_type;

typedef struct	s_ctx
{
	t_win_data		window;
	t_state_type	state;
	uint64_t		keystates;
	t_map_inf		tile_map;
	t_minimap_inf	minimap;
	t_player		player;
	t_texture_inf	textures[6];
}				t_ctx;

typedef void	t_statefn(t_ctx *ctx);
typedef int		t_state_evtfn(t_ctx *ctx, SDL_Event evt);

typedef struct	s_state_inf
{
	t_statefn		*init_fn;
	t_statefn		*quit_fn;
	t_statefn		*run_fn;
	t_state_evtfn	*evt_fn;
}				t_state_inf;

typedef struct	s_draw_ctx
{
	int	wall_height;
	int	wall_top;
	int	wall_screen_height;
	int	wall_screen_top;
}				t_draw_ctx;

void			place_player_map(t_map_inf *map_inf, t_tile_inf *tile_inf);
t_map_inf		load_mapfile(const char *file, t_error *err);
t_error			load_texture(const char *file, t_texture_inf *text_inf);

void			wolf3d_events(t_ctx *ctx);
t_error			wolf3d_init(t_ctx *ctx, const char *mapfile);
void			wolf3d_run(t_ctx *ctx);
void			wolf3d_clean(t_ctx *ctx);

void			wolf3d_main_menu(t_ctx *ctx);
void			wolf3d_play_init(t_ctx *ctx);
void			wolf3d_play_run(t_ctx *ctx);
int				wolf3d_play_events(t_ctx *ctx, SDL_Event event);

void			setup_draw_ctx(t_ctx *ctx, t_ray_inf *ray_inf
	, t_draw_ctx *draw_ctx);
void			draw_texture(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *ray_inf, t_texture_inf *text_inf);
void			draw_column(t_ctx *ctx, t_column_inf *column_inf
	, t_ray_inf *ray_inf);

void			player_view_thread(t_thread_inf *thread_inf);
void			player_view_raycast(t_ctx *ctx);
void			player_movement(t_ctx *ctx);

t_ray_inf		launch_ray(t_vec2d origin, double angle, t_map_inf *map_inf);
void			check_collision_after_move(t_ctx *ctx, t_vec2d old_position);

t_error			minimap_setup(t_ctx *ctx);
void			minimap_destroy(t_minimap_inf *minimap);
void			minimap_reset_z_buffer(t_ctx *ctx);
void			minimap_background(t_ctx *ctx);
void			minimap_ray(t_ctx *ctx, double length, double angle);
void			draw_minimap_view(t_ctx *ctx);

t_ray_inf		launch_portal_ray(t_ray_inf *hit_inf, t_map_inf *map_inf);
void			teleport_through_portal(t_ctx *ctx, t_tile_meta *tile);

#endif
