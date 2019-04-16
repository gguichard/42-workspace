/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:09:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 12:09:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"
#include "parser.h"

t_json_token	*read_json_key_pair(t_list **lst, int depth_level)
{
	char			*key;
	t_json_token	*token;

	if (((t_json_lexeme *)(*lst)->content)->type != TK_STRING)
		return (NULL);
	key = ft_strdup(((t_json_lexeme *)(*lst)->content)->value);
	if (key != NULL && (*lst = (*lst)->next) != NULL
			&& expect_json_sep(lst, ":"))
	{
		token = eat_json_lexemes(lst, depth_level);
		if (token != NULL)
		{
			token->key = key;
			return (token);
		}
	}
	free(key);
	return (NULL);
}

t_json_token	*parse_json(const char *data)
{
	t_list			*lst;
	t_list			*curr;
	t_json_token	*root;

	lst = split_str_into_json_lexemes(data);
	debug_lexemes(lst);
	if (lst == NULL)
		return (NULL);
	root = NULL;
	if (!check_for_unknown_lexeme_type(lst))
	{
		curr = lst;
		root = eat_json_lexemes(&curr, 1);
	}
	ft_lstdel(&lst, del_json_lexeme);
	return (root);
}
