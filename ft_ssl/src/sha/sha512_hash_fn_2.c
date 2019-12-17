/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash_fn_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 13:11:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "utils.h"

uint64_t	sha512_hash_bsig0(uint64_t x)
{
	return (rotate_right64(x, 28)
		^ rotate_right64(x, 34)
		^ rotate_right64(x, 39));
}

uint64_t	sha512_hash_bsig1(uint64_t x)
{
	return (rotate_right64(x, 14)
		^ rotate_right64(x, 18)
		^ rotate_right64(x, 41));
}

uint64_t	sha512_hash_ssig0(uint64_t x)
{
	return (rotate_right64(x, 1)
		^ rotate_right64(x, 8)
		^ (x >> 7));
}

uint64_t	sha512_hash_ssig1(uint64_t x)
{
	return (rotate_right64(x, 19)
		^ rotate_right64(x, 61)
		^ (x >> 6));
}
