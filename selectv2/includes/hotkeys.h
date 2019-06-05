/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotkeys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 11:50:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/05 13:02:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTKEYS_H
# define HOTKEYS_H

# define HOTKEY_ESC 1
# define HOTKEY_ENTER 2
# define HOTKEY_SPACE 3
# define HOTKEY_ARROW_LEFT 4
# define HOTKEY_ARROW_RIGHT 5
# define HOTKEY_BACKSPACE 6
# define HOTKEY_DELETE 7

typedef struct		s_hotkey
{
	int				type;
	const char		*buffer;
	void			(*hook_fn)(int);
}					t_hotkey;

void				add_hotkey(t_list **hotkeys, int type, const char *buffer
	, void (*hook_fn)(int));
int					hotkey_match(t_list *hotkeys, const char *buffer);

#endif
