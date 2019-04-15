/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:41:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 16:43:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define TK_STRING 1
# define TK_OPEN_OBJECT 2
# define TK_CLOSE_OBJECT 3
# define TK_OPEN_ARRAY 4
# define TK_CLOSE_ARRAY 5
# define TK_NUMBER 6
# define TK_PRIMITIVE 7
# define TK_SEPARATOR 8
# define TK_UNKNOWN 9

# define BRACKET_CHARS "{}[]"
# define SEPARATOR_CHARS ","

typedef struct	s_token
{
	int			type;
	char		*value;
}				t_token;

t_list			*split_str_into_tokens(const char *str);

#endif
