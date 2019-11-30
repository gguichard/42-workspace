/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_inf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:21:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 13:50:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_INF_H
# define THREAD_INF_H

# include <SDL.h>
# include <stdint.h>

typedef struct	s_thread_inf
{
	void		*data;
	SDL_Thread	*thread;
	int			x_start;
}				t_thread_inf;

#endif
