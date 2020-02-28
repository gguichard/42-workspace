/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_hash_fn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:10:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 12:11:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	sha1_hash_1(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (~b & d));
}

uint32_t	sha1_hash_2(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	sha1_hash_3(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (b & d) | (c & d));
}

uint32_t	sha1_hash_4(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}
