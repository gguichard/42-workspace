/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:38:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/19 12:45:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

# define UTILS_ROTATE_LEFT32 "../utils/rotate_left32.c"
# define UTILS_ROTATE_LEFT64 "../utils/rotate_left64.c"
# define UTILS_ROTATE_RIGHT32 "../utils/rotate_right32.c"
# define UTILS_ROTATE_RIGHT64 "../utils/rotate_right64.c"

uint32_t	byte_swap32(uint32_t x);
uint64_t	byte_swap64(uint64_t x);
void		digest_hex(char buffer[2], uint8_t byte);

#endif
