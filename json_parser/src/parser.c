/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:09:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 10:40:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"
#include "parser.h"

static void			*del_json_token(t_json_token *token)
{
	t_json_token	*curr;
	t_json_token	*next;

	free(token->key);
	if (token->type == JSON_STRING)
		free(token->value.str);
	else if (token->type == JSON_ARRAY || token->type == JSON_OBJECT)
	{
		curr = token->value.child;
		while (curr != NULL)
		{
			next = curr->next;
			del_json_token(curr);
			curr = next;
		}
	}
	free(token);
	return (NULL);
}

static int			check_for_unknown_lexeme_type(t_list *lst)
{
	t_list	*curr;

	if (lst == NULL)
		return (1);
	curr = lst;
	while (curr->next != NULL)
		curr = curr->next;
	return (((t_json_lexeme *)curr->content)->type == TK_UNKNOWN);
}

static int			expect_json_sep(t_list **lst, const char *sep)
{
	t_json_lexeme *lexeme;

	lexeme = (t_json_lexeme *)(*lst)->content;
	if (lexeme->type == TK_SEPARATOR && ft_strequ(lexeme->value, sep))
	{
		*lst = (*lst)->next;
		return (*lst != NULL);
	}
	return (0);
}

static t_json_token	*eat_json_lexemes(t_list **lst, int depth_level)
{
	t_json_token	*token;
	t_json_lexeme	*lexeme;

	token = (t_json_token *)ft_memalloc(sizeof(t_json_token));
	if (token == NULL)
		return (NULL);
	token->type = JSON_UNKNOWN;
	lexeme = (t_json_lexeme *)(*lst)->content;
	if (lexeme->type == TK_STRING)
	{
		token->value.str = ft_strdup(lexeme->value);
		if (token->value.str != NULL)
			token->type = JSON_STRING;
	}
	else if (lexeme->type == TK_NUMBER)
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
	else if (lexeme->type == TK_PRIMITIVE)
	{
		if (lexeme->value[0] == 'n')
			token->type = JSON_NULL;
		else
		{
			token->type = JSON_BOOLEAN;
			token->value.i = (lexeme->value[0] == 't');
		}
	}
	else if (lexeme->type == TK_OPEN_OBJECT)
	{
		if (read_json_object(lst, depth_level + 1, token))
			token->type = JSON_OBJECT;
	}
	if (token->type == JSON_UNKNOWN)
	{
		del_json_token(token);
		return (NULL);
	}
	return (token);
}

static t_json_token	*read_json_key_pair(t_list **lst, int depth_level)
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

int					read_json_object(t_list **lst, int depth_level
		, t_json_token *token)
{
	t_json_token	*child;

	if (depth_level > JSON_MAX_DEPTH)
		return (0);
	while (*lst != NULL && (*lst = (*lst)->next) != NULL)
	{
		if (((t_json_lexeme *)(*lst)->content)->type == TK_CLOSE_OBJECT)
			return (1);
		if (token->value.child != NULL && !expect_json_sep(lst, ","))
			break ;
		child = read_json_key_pair(lst, depth_level + 1);
		if (child == NULL)
			break ;
		child->next = token->value.child;
		token->value.child = child;
		if (child->next != NULL)
			child->next->prev = child;
	}
	return (0);
}

t_json_token		*parse_json(const char *data)
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
