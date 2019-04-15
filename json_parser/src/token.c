/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:01:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 16:46:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"

static void	del_token(void *content, size_t content_size)
{
	(void)content_size;
	free(((t_token *)content)->value);
	free(content);
}

static int	create_token_with_type(t_list **lst, int type, const char *str
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

int			create_bracket_token(t_list **lst, char bracket_char)
{
	int	ret;

	ret = 0;
	if (bracket_char == '{')
		ret = create_token_with_type(lst, TK_OPEN_OBJECT, "{", 1);
	else if (bracket_char == '}')
		ret = create_token_with_type(lst, TK_CLOSE_OBJECT, "}", 1);
	else if (bracket_char == '[')
		ret = create_token_with_type(lst, TK_OPEN_ARRAY, "[", 1);
	else if (bracket_char == ']')
		ret = create_token_with_type(lst, TK_CLOSE_ARRAY, "]", 1);
	return (ret);
}

t_list		*split_str_into_tokens(const char *str)
{
	t_list	*lst;
	size_t	idx;
	int		ret;

	lst = NULL;
	idx = 0;
	while (str[idx] != '\0')
	{
		ret = 0;
		if (ft_strchr(BRACKET_CHARS, str[idx]) != NULL)
			ret = create_bracket_token(&lst, str[idx]);
		else if (ft_strchr(SEPARATOR_CHARS, str[idx]) != NULL)
			ret = create_token_with_type(&lst, TK_SEPARATOR, str + idx, 1);
		if (ret == 0)
		{
			if (!create_token_with_type(&lst, TK_UNKNOWN, NULL, 0))
				ft_lstdel(&lst, del_token);
			break ;
		}
		idx += ret;
	}
	return (lst);
}
