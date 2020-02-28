/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash_fn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:21:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 13:11:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint64_t	sha512_hash_ch(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (~x & z));
}

uint64_t	sha512_hash_maj(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
