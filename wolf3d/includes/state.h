/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:58:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 19:00:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

typedef struct s_ctx	t_ctx;

typedef enum	e_state_type
{
	MAIN_MENU = 0,
	PLAYING = 1,
	OPTIONS = 2,
	QUIT = 3,
	STATE_LAST = 4
}				t_state_type;

typedef void	t_statefn(t_ctx *ctx);
typedef int		t_state_evtfn(t_ctx *ctx, SDL_Event evt);

typedef struct	s_state_inf
{
	t_statefn		*init_fn;
	t_statefn		*quit_fn;
	t_statefn		*run_fn;
	t_state_evtfn	*evt_fn;
}				t_state_inf;

#endif
