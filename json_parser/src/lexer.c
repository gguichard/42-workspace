/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:01:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 13:13:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

void			skip_json_number_digits(const char *str, size_t *offset)
{
	while (ft_isdigit(str[*offset]))
		*offset += 1;
}

void			escape_characters_in_lexeme(t_json_lexeme *lexeme)
{
	char	*offset;

	offset = lexeme->value;
	while (1)
	{
		offset = ft_strchr(offset, '\\');
		if (offset == NULL)
			break ;
		if (offset[1] == '\\' || offset[1] == '\"' || offset[1] == '/')
			ft_memmove(offset, offset + 1, ft_strlen(offset));
		offset += 1;
	}
}

void			del_json_lexeme(void *content, size_t content_size)
{
	(void)content_size;
	free(((t_json_lexeme *)content)->value);
	free(content);
}

static size_t	analyze_json_str(t_list **lst, const char *str)
{
	size_t	ret;

	ret = 0;
	if (ft_isspace(*str))
		ret = 1;
	else if (ft_strchr(BRACKET_CHARS, *str) != NULL)
		ret = create_bracket_lexeme(lst, *str);
	else if (ft_strchr(SEPARATOR_CHARS, *str) != NULL)
		ret = create_lexeme_with_type(lst, TK_SEPARATOR, str, 1)
			!= NULL;
	else if (ft_strchr(NUMBER_CHARS, *str) != NULL)
		ret = create_number_lexeme(lst, str);
	else if (ft_strchr(PRIMITIVE_CHARS, *str))
		ret = create_primitive_lexeme(lst, str);
	else if (*str == '\"')
		ret = create_string_lexeme(lst, str);
	return (ret);
}

t_list			*split_str_into_json_lexemes(const char *str)
{
	t_list	*lst;
	size_t	idx;
	size_t	ret;

	lst = NULL;
	idx = 0;
	while (str[idx] != '\0')
	{
		ret = analyze_json_str(&lst, str + idx);
		if (ret == 0 && create_lexeme_with_type(&lst, TK_UNKNOWN, str + idx
					, ft_strlen(str + idx)) == NULL)
			ft_lstdel(&lst, del_json_lexeme);
		if (ret == 0)
			break ;
		idx += ret;
	}
	return (lst);
}
