/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:01:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 18:04:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"

static void		del_token(void *content, size_t content_size)
{
	(void)content_size;
	free(((t_token *)content)->value);
	free(content);
}

static int		create_token_with_type(t_list **lst, int type, const char *str
		, size_t len)
{
	t_token	token;
	t_list	*elem;

	token.type = type;
	token.value = (str == NULL ? NULL : ft_strsub(str, 0, len));
	if (token.value == NULL && str != NULL)
		return (0);
	elem = ft_lstnew(&token, sizeof(t_token));
	if (elem == NULL)
	{
		free(token.value);
		return (0);
	}
	ft_lstpush(lst, elem);
	return (1);
}

static size_t	create_bracket_token(t_list **lst, char bracket_char)
{
	int	ret;

	if (bracket_char == '{')
		ret = create_token_with_type(lst, TK_OPEN_OBJECT, "{", 1);
	else if (bracket_char == '}')
		ret = create_token_with_type(lst, TK_CLOSE_OBJECT, "}", 1);
	else if (bracket_char == '[')
		ret = create_token_with_type(lst, TK_OPEN_ARRAY, "[", 1);
	else if (bracket_char == ']')
		ret = create_token_with_type(lst, TK_CLOSE_ARRAY, "]", 1);
	else
		ret = 0;
	return (ret);
}

static void		skip_digits(const char *str, size_t *offset)
{
	while (ft_isdigit(str[*offset]))
		*offset += 1;
}

static size_t	create_number_token(t_list **lst, const char *str)
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
		skip_digits(str, &offset);
	if (str[offset] == '.')
	{
		offset++;
		if (!ft_isdigit(str[offset]))
			return (0);
		skip_digits(str, &offset);
	}
	// TODO: gerer forme exponentielle
	if (!create_token_with_type(lst, TK_NUMBER, str, offset))
		return (0);
	return (offset);
}

static size_t	create_primitive_token(t_list **lst, const char *str)
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
	if (offset > 0 && !create_token_with_type(lst, TK_PRIMITIVE, str, offset))
		return (0);
	return (offset);
}

static size_t	create_string_token(t_list **lst, const char *str)
{
	size_t	offset;

	offset = 1;
	while (str[offset] != '\0' && str[offset] != '\"')
		offset++;
	if (str[offset] != '\"')
		return (0);
	offset++;
	// TODO: gerer Unicode + backslash
	if (!create_token_with_type(lst, TK_STRING, str + 1, offset - 2))
		return (0);
	return (offset);
}

t_list			*split_str_into_tokens(const char *str)
{
	t_list	*lst;
	size_t	idx;
	size_t	ret;

	lst = NULL;
	idx = 0;
	while (str[idx] != '\0')
	{
		ret = 0;
		if (ft_isspace(str[idx]))
			ret = 1;
		else if (ft_strchr(BRACKET_CHARS, str[idx]) != NULL)
			ret = create_bracket_token(&lst, str[idx]);
		else if (ft_strchr(SEPARATOR_CHARS, str[idx]) != NULL)
			ret = create_token_with_type(&lst, TK_SEPARATOR, str + idx, 1);
		else if (ft_strchr(NUMBER_CHARS, str[idx]) != NULL)
			ret = create_number_token(&lst, str + idx);
		else if (ft_strchr(PRIMITIVE_CHARS, str[idx]))
			ret = create_primitive_token(&lst, str + idx);
		else if (str[idx] == '\"')
			ret = create_string_token(&lst, str + idx);
		if (ret == 0 && !create_token_with_type(&lst, TK_UNKNOWN, str + idx
					, ft_strlen(str + idx)))
			ft_lstdel(&lst, del_token);
		if (ret == 0)
			break ;
		idx += ret;
	}
	return (lst);
}
