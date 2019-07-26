/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:35:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/26 18:52:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZONE_H
# define ZONE_H

# include "region.h"

typedef struct	s_zone
{
	t_region		*tiny_region;
	t_region		*small_region;
	t_large_block	*large_list;
}				t_zone;

#endif
