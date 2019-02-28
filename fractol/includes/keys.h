/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 02:37:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 09:38:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_ESC 53
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MOUSELEFT 1
# define KEY_SCROLLUP 4
# define KEY_SCROLLDOWN 5
# define KEY_R 15
# define KEY_TAB 48
# define KEY_ARROWUP 126
# define KEY_ARROWDOWN 125
# define KEY_ARROWLEFT 123
# define KEY_ARROWRIGHT 124
# define KEY_PAGEUP 116
# define KEY_PAGEDOWN 121
# define KEY_SHIFT 257
# define KEY_A 0

typedef struct	s_keys
{
	int			iters;
	int			show_hud;
	int			x_move;
	int			y_move;
}				t_keys;

#endif
