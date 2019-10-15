/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:11:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 09:03:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_LIST_H
# define ALLOC_LIST_H

typedef struct	alloc_list
{
	void				*data;
	struct alloc_list	*next;
} alloc_list_t;

alloc_list_t	*push_alloc(alloc_list_t **lst, void *data);
void			del_alloc_list(alloc_list_t **lst, void (*fn)(void *));

#endif
