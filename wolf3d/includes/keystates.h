/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keystates.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:31:20 by gguichar          #+#    #+#             */
/*   Updated: 2019/12/15 13:40:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYSTATES_H
# define KEYSTATES_H

# include <stdint.h>

# define ESC_KEY 0x1
# define ENTER_KEY 0x2
# define MOVE_FORWARD_KEY 0x4
# define MOVE_BACKWARD_KEY 0x8
# define STRAFE_LEFT_KEY 0x10
# define STRAFE_RIGHT_KEY 0x20
# define ROTATE_LEFT_KEY 0x40
# define ROTATE_RIGHT_KEY 0x80

typedef struct	s_key
{
	int			keycode;
	uint64_t	bitmask;
}				t_key;

#endif
