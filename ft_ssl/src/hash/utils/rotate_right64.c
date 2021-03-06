/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_right64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:33:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/19 12:34:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static uint64_t	rotate_right64(uint64_t x, int s)
{
	return ((x >> s) | (x << (64 - s)));
}
