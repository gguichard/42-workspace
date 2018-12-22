/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:13:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/21 13:14:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATIONS_H
# define ROTATIONS_H

# include "rotations.h"

int	swap(t_list **lst);
int	push(t_list **to, t_list **from);
int	rotate(t_list **lst);
int	rev_rotate(t_list **lst);

#endif
