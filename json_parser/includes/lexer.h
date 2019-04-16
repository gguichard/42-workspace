/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:41:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 13:09:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

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
# define SEPARATOR_CHARS ",:"
# define NUMBER_CHARS "-0123456789"
# define PRIMITIVE_CHARS "ftn"
# define BACKSLASH_CHARS "\"\\/bfnrt"

# define TRUE_PRIMITIVE "true"
# define FALSE_PRIMITIVE "false"
# define NULL_PRIMITIVE "null"

typedef struct	s_json_lexeme
{
	int			type;
	char		*value;
}				t_json_lexeme;

t_json_lexeme	*create_lexeme_with_type(t_list **lst, int type, const char *str
		, size_t len);
size_t			create_bracket_lexeme(t_list **lst, char bracket_char);
size_t			create_string_lexeme(t_list **lst, const char *str);
size_t			create_number_lexeme(t_list **lst, const char *str);
size_t			create_primitive_lexeme(t_list **lst, const char *str);

void			skip_json_number_digits(const char *str, size_t *offset);
void			escape_characters_in_lexeme(t_json_lexeme *lexeme);
void			del_json_lexeme(void *content, size_t content_size);
t_list			*split_str_into_json_lexemes(const char *str);

#endif
