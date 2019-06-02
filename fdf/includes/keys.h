/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:05:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/02 13:35:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_ESCAPE 53

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

# define KEY_PLUS 24
# define KEY_MINUS 27

# define KEY_PAGE_UP 116
# define KEY_PAGE_DOWN 121

# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124
# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125

# define KEY_MOUSE_LEFT 1

# define TRANSLATE_X_LEFT (1 << 0)
# define TRANSLATE_X_RIGHT (1 << 1)
# define TRANSLATE_Y_UP (1 << 2)
# define TRANSLATE_Y_DOWN (1 << 3)
# define SCALE_IN (1 << 4)
# define SCALE_OUT (1 << 5)
# define DEPTH_INCREASE (1 << 6)
# define DEPTH_DECREASE (1 << 7)
# define ROTATE_LEFT (1 << 8)
# define ROTATE_RIGHT (1 << 9)

#endif
