/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:21:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/26 22:48:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include <string.h>

# define MD5_FUN_F(x, y, z) ((x & y) | (~x & z))
# define MD5_FUN_G(x, y, z) ((x & z) | (y & ~z))
# define MD5_FUN_H(x, y, z) (x ^ y ^ z)
# define MD5_FUN_I(x, y, z) (y ^ (x | ~z))
# define MD5_ROTATELEFT(n, s) ((n << s) | (n >> (sizeof(n) * 8 - s)))

typedef struct	s_md5_step
{
	size_t		word_index;
	int			shift_rotate;
	uint32_t	sine;
}				t_md5_step;

void			md5_print_digest(uint32_t states[4]);
void			md5_hash(const uint8_t *bytes, size_t len);

#endif
