/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash_fn_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:10:28 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 13:11:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "utils.h"

uint32_t	sha256_hash_bsig0(uint32_t x)
{
	return (rotate_right32(x, 2)
		^ rotate_right32(x, 13)
		^ rotate_right32(x, 22));
}

uint32_t	sha256_hash_bsig1(uint32_t x)
{
	return ((rotate_right32(x, 6))
		^ rotate_right32(x, 11)
		^ rotate_right32(x, 25));
}

uint32_t	sha256_hash_ssig0(uint32_t x)
{
	return (rotate_right32(x, 7)
		^ rotate_right32(x, 18)
		^ (x >> 3));
}

uint32_t	sha256_hash_ssig1(uint32_t x)
{
	return (rotate_right32(x, 17)
		^ rotate_right32(x, 19)
		^ (x >> 10));
}
