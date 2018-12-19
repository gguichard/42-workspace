/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:39:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/19 19:25:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

int	apply_sets(int count, t_list **a, t_list **b);

/*
** INSTRUCTIONS.
*/
void	swap(t_list **lst);
void	push(t_list **to, t_list **from);
void	rotate(t_list **lst);
void	rev_rotate(t_list **lst);

#endif
