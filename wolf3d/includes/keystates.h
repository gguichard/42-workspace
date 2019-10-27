/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keystates.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:31:20 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/27 23:15:21 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYSTATES_H
# define KEYSTATES_H

# include <stdint.h>

# define ESC_KEY (1 << 0)
# define ENTER_KEY (1 << 1)
# define MOVE_FORWARD_KEY (1 << 2)
# define MOVE_BACKWARD_KEY (1 << 3)
# define STRAFE_LEFT_KEY (1 << 4)
# define STRAFE_RIGHT_KEY (1 << 5)

typedef struct	s_key
{
	int			keycode;
	uint64_t	bitmask;
}				t_key;

#endif
