/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:03:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 12:22:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"
#include "parser.h"

static void		read_json_string(t_json_lexeme *lexeme, t_json_token *token)
{
	token->value.str = ft_strdup(lexeme->value);
	if (token->value.str != NULL)
		token->type = JSON_STRING;
}

static void		read_json_number(t_json_lexeme *lexeme, t_json_token *token)
{
	if (ft_strchr(lexeme->value, '.') != NULL)
	{
		token->type = JSON_FLOAT;
		token->value.f = atof(lexeme->value);
		// TODO: remplacer atof par ft_atof
	}
	else
	{
		token->type = JSON_INTEGER;
		token->value.i = ft_atoi(lexeme->value);
	}
}

static void		read_json_primitive(t_json_lexeme *lexeme, t_json_token *token)
{
	if (lexeme->value[0] == 'n')
		token->type = JSON_NULL;
	else
	{
		token->type = JSON_BOOLEAN;
		token->value.i = (lexeme->value[0] == 't');
	}
}

static int		read_json_object_or_array(t_list **lst, int depth_level
		, t_json_token *token, int is_object)
{
	t_json_token	*child;

	while (*lst != NULL && (*lst = (*lst)->next) != NULL)
	{
		if (((t_json_lexeme *)(*lst)->content)->type
				== (is_object ? TK_CLOSE_OBJECT : TK_CLOSE_ARRAY))
			return (1);
		if (token->value.child != NULL && !expect_json_sep(lst, ","))
			break ;
		child = is_object
			? read_json_key_pair(lst, depth_level + 1)
			: eat_json_lexemes(lst, depth_level + 1);
		if (child == NULL)
			break ;
		child->next = token->value.child;
		token->value.child = child;
		if (child->next != NULL)
			child->next->prev = child;
	}
	return (0);
}

t_json_token	*eat_json_lexemes(t_list **lst, int depth_level)
{
	t_json_token	*token;
	t_json_lexeme	*lexeme;

	if (depth_level > JSON_MAX_DEPTH)
		return (NULL);
	if ((token = (t_json_token *)ft_memalloc(sizeof(t_json_token))) == NULL)
		return (NULL);
	token->type = JSON_UNKNOWN;
	lexeme = (t_json_lexeme *)(*lst)->content;
	if (lexeme->type == TK_STRING)
		read_json_string(lexeme, token);
	else if (lexeme->type == TK_NUMBER)
		read_json_number(lexeme, token);
	else if (lexeme->type == TK_PRIMITIVE)
		read_json_primitive(lexeme, token);
	else if (lexeme->type == TK_OPEN_OBJECT || lexeme->type == TK_OPEN_ARRAY)
	{
		if (read_json_object_or_array(lst, depth_level, token
					, lexeme->type == TK_OPEN_OBJECT))
			token->type = (lexeme->type == TK_OPEN_OBJECT
					? JSON_OBJECT : JSON_ARRAY);
	}
	if (token->type == JSON_UNKNOWN)
		return (del_json_token(token));
	return (token);
}
