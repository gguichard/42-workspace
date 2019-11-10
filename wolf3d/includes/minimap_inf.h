/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_inf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:11:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 14:53:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_INF_H
# define MINIMAP_INF_H

# include <stdint.h>

typedef struct	s_minimap_inf
{
	int			size;
	int			view_radius;
	uint32_t	*pixels;
}				t_minimap_inf;

#endif
