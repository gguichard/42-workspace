/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:25:33 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 12:28:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "utils.h"

uint32_t	rotate_left32(uint32_t x, int s)
{
	return ((x << s) | (x >> (32 - s)));
}

uint64_t	rotate_left64(uint64_t x, int s)
{
	return ((x << s) | (x >> (64 - s)));
}

uint32_t	rotate_right32(uint32_t x, int s)
{
	return ((x >> s) | (x << (32 - s)));
}

uint64_t	rotate_right64(uint64_t x, int s)
{
	return ((x >> s) | (x << (64 - s)));
}
