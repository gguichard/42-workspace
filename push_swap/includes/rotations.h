/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:13:30 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/27 17:52:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATIONS_H
# define ROTATIONS_H

# include "libft.h"
# include "rotations.h"

int	ps_swap(t_list **lst);
int	ps_push(t_list **to, t_list **from);
int	ps_rotate(t_list **lst);
int	ps_rev_rotate(t_list **lst);

#endif
