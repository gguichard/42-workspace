/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:03:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 18:08:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"

void			read_json_string(t_json_lexeme *lexeme, t_json_token *token)
{
	token->value.str = ft_strdup(lexeme->value);
	if (token->value.str != NULL)
		token->type = JSON_STRING;
}

void			read_json_number(t_json_lexeme *lexeme, t_json_token *token)
{
	if (ft_strchr(lexeme->value, '.') != NULL)
	{
		token->type = JSON_FLOAT;
		token->value.f = ft_bad_atof(lexeme->value);
	}
	else
	{
		token->type = JSON_INTEGER;
		token->value.i = ft_atoi(lexeme->value);
	}
}

void			read_json_primitive(t_json_lexeme *lexeme, t_json_token *token)
{
	if (lexeme->value[0] == 'n')
		token->type = JSON_NULL;
	else
	{
		token->type = JSON_BOOLEAN;
		token->value.i = (lexeme->value[0] == 't');
	}
}

int				read_json_object_or_array(t_list **lst, int depth_level
		, t_json_token *token, int is_object)
{
	t_json_token	*child;

	while (*lst != NULL)
	{
		if (((t_json_lexeme *)(*lst)->content)->type
				== (is_object ? TK_CLOSE_OBJECT : TK_CLOSE_ARRAY))
			return (1);
		if (token->value.child != NULL && !expect_json_sep(lst, ","))
			break ;
		child = is_object
			? read_json_key_pair(lst, depth_level)
			: eat_json_lexemes(lst, depth_level);
		if (child == NULL)
			break ;
		push_json_token_child(token, child);
	}
	del_json_token_childs(token);
	return (0);
}

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
