/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_inf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:32:57 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 17:40:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLUMN_INF_H
# define COLUMN_INF_H

typedef struct	s_column_inf
{
	int			x;
	uint32_t	pixels[720];
	double		fisheye_angle;
}				t_column_inf;

#endif
