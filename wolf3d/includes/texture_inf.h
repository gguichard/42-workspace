/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_inf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:01:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/03 10:23:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_INF_H
# define TEXTURE_INF_H

# include <stdint.h>

typedef struct	s_texture_inf
{
	int			width;
	int			height;
	uint32_t	*pixels;
}				t_texture_inf;

#endif
