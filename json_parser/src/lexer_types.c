/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:03:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 13:09:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

t_json_lexeme	*create_lexeme_with_type(t_list **lst, int type, const char *str
		, size_t len)
{
	t_json_lexeme	lexeme;
	t_list			*elem;

	lexeme.type = type;
	lexeme.value = (str == NULL ? NULL : ft_strsub(str, 0, len));
	if (lexeme.value == NULL && str != NULL)
		return (NULL);
	elem = ft_lstnew(&lexeme, sizeof(t_json_lexeme));
	if (elem == NULL)
	{
		free(lexeme.value);
		return (NULL);
	}
	ft_lstpush(lst, elem);
	return ((t_json_lexeme *)elem->content);
}

size_t			create_bracket_lexeme(t_list **lst, char bracket_char)
{
	int	ret;

	if (bracket_char == '{')
		ret = create_lexeme_with_type(lst, TK_OPEN_OBJECT, "{", 1) != NULL;
	else if (bracket_char == '}')
		ret = create_lexeme_with_type(lst, TK_CLOSE_OBJECT, "}", 1) != NULL;
	else if (bracket_char == '[')
		ret = create_lexeme_with_type(lst, TK_OPEN_ARRAY, "[", 1) != NULL;
	else if (bracket_char == ']')
		ret = create_lexeme_with_type(lst, TK_CLOSE_ARRAY, "]", 1) != NULL;
	else
		ret = 0;
	return (ret);
}

size_t			create_string_lexeme(t_list **lst, const char *str)
{
	size_t			offset;
	t_json_lexeme	*lexeme;

	offset = 1;
	// TODO: gerer les points unicode avec \u
	while (str[offset] != '\0' && str[offset] != '\"')
	{
		if (str[offset] != '\\')
			offset++;
		else if (ft_strchr(BACKSLASH_CHARS, str[offset + 1]) != NULL)
			offset += 2;
		else
			return (0);
	}
	if (str[offset] != '\"')
		return (0);
	offset++;
	lexeme = create_lexeme_with_type(lst, TK_STRING, str + 1, offset - 2);
	if (lexeme == NULL)
		return (0);
	escape_characters_in_lexeme(lexeme);
	return (offset);
}

size_t			create_number_lexeme(t_list **lst, const char *str)
{
	size_t	offset;

	offset = 0;
	if (str[offset] == '-')
		offset++;
	if (!ft_isdigit(str[offset]))
		return (0);
	if (str[offset] == '0')
		offset++;
	else
		skip_json_number_digits(str, &offset);
	if (str[offset] == '.')
	{
		offset++;
		if (!ft_isdigit(str[offset]))
			return (0);
		skip_json_number_digits(str, &offset);
	}
	// TODO: gerer forme exponentielle
	if (create_lexeme_with_type(lst, TK_NUMBER, str, offset) == NULL)
		return (0);
	return (offset);
}

size_t			create_primitive_lexeme(t_list **lst, const char *str)
{
	size_t	offset;

	offset = 0;
	if (*str == 't'
			&& ft_strnequ(str, TRUE_PRIMITIVE, ft_strlen(TRUE_PRIMITIVE)))
		offset = ft_strlen(TRUE_PRIMITIVE);
	else if (*str == 'f'
			&& ft_strnequ(str, FALSE_PRIMITIVE, ft_strlen(FALSE_PRIMITIVE)))
		offset = ft_strlen(FALSE_PRIMITIVE);
	else if (*str == 'n'
			&& ft_strnequ(str, NULL_PRIMITIVE, ft_strlen(NULL_PRIMITIVE)))
		offset = ft_strlen(NULL_PRIMITIVE);
	if (offset > 0
			&& create_lexeme_with_type(lst, TK_PRIMITIVE, str, offset) == NULL)
		return (0);
	return (offset);
}
