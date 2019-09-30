/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:30:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/30 23:00:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA2_H
# define FT_SSL_SHA2_H

# include <stdint.h>
# include <string.h>
# include "ft_ssl.h"

# define RR UTILS_ROTATERIGHT

# define SHA2_HASH_CH(x, y, z) ((x & y) ^ (~x & z))
# define SHA2_HASH_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
# define SHA2_HASH_BSIG0(x) ((RR(x, 2)) ^ (RR(x, 13)) ^ (RR(x, 22)))
# define SHA2_HASH_BSIG1(x) ((RR(x, 6)) ^ (RR(x, 11)) ^ (RR(x, 25)))
# define SHA2_HASH_SSIG0(x) ((RR(x, 7)) ^ (RR(x, 18)) ^ ((x) >> 3))
# define SHA2_HASH_SSIG1(x) ((RR(x, 17)) ^ (RR(x, 19)) ^ ((x) >> 10))

void	sha256_stream_init(t_hash_stream *stream);
void	sha256_roll(uint32_t hash[8], uint32_t words[64]);

void	sha256_digest(char buffer[65], uint32_t states[4]);

#endif
