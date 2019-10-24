/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:38:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/24 10:57:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define UTILS_MIN(x, y) (x > y ? y : x)
# define UTILS_ROTATELEFT(n, s) (((n) << s) | ((n) >> (sizeof(n) * 8 - s)))
# define UTILS_ROTATERIGHT(n, s) (((n) >> s) | ((n) << (sizeof(n) * 8 - s)))

# include <stdint.h>

uint32_t	byte_swap32(uint32_t x);
uint64_t	byte_swap64(uint64_t x);
void		digest_hex(char buffer[2], uint8_t byte);

#endif
