/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:38:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/17 13:01:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

uint32_t	byte_swap32(uint32_t x);
uint64_t	byte_swap64(uint64_t x);
void		digest_hex(char buffer[2], uint8_t byte);

uint32_t	rotate_left32(uint32_t x, int s);
uint64_t	rotate_left64(uint64_t x, int s);
uint32_t	rotate_right32(uint32_t x, int s);
uint64_t	rotate_right64(uint64_t x, int s);

#endif
