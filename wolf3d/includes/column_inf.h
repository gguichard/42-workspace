/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_inf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:32:57 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/30 14:36:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLUMN_INF_H
# define COLUMN_INF_H

typedef struct	s_column_inf
{
	int	x;
	int	current_z;
	int	z_buffer[960];
	int	use_z_buffer;
	int	depth;
}				t_column_inf;

#endif
