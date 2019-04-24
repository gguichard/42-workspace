/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:30:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/24 16:43:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_vec(void *ptr)
{
	free(ptr);
}

void		ft_vecfree(t_vector *vector)
{
	ft_vecdel(vector, free_vec);
}
