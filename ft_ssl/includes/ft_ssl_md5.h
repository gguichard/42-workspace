/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:21:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/30 23:00:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include <string.h>

# define MD5_HASH_F(x, y, z) ((x & y) | (~x & z))
# define MD5_HASH_G(x, y, z) ((x & z) | (y & ~z))
# define MD5_HASH_H(x, y, z) (x ^ y ^ z)
# define MD5_HASH_I(x, y, z) (y ^ (x | ~z))

void	md5_stream_init(t_hash_stream *stream);
void	md5_roll(uint32_t hash[4], uint32_t words[16]);

void	md5_digest(char buffer[33], uint32_t hash[4]);

#endif
