/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:09:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 00:18:35 by gguichar         ###   ########.fr       */
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

static void			set_json_token_type(t_json_lexeme *lexeme
		, t_json_token *token, int depth_value)
{
	(void)depth_value;
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

static t_json_token	*read_json_key_pair(t_list **lst, int depth_value)
{
	char			*key;
	t_json_token	*token;

	if (((t_json_lexeme *)(*lst)->content)->type != TK_STRING)
		return (NULL);
	key = ((t_json_lexeme *)(*lst)->content)->value;
	if ((*lst = (*lst)->next) == NULL || !expect_json_sep(lst, ":"))
		return (NULL);
	token = (t_json_token *)ft_memalloc(sizeof(t_json_token));
	if (token == NULL)
		return (NULL);
	token->key = ft_strdup(key);
	if (token->key == NULL)
		ft_memdel((void **)&token);
	else
		set_json_token_type((t_json_lexeme *)(*lst)->content, token
				, depth_value);
	if (token->type == JSON_UNKNOWN)
		return (del_json_token(token));
	return (token);
}

// TODO: passer le t_json_token en argument plutot que de le malloc dans la fonction
t_json_token		*read_json_object(t_list **lst, int depth_level)
{
	t_json_token	*token;
	t_json_token	*child;

	if (depth_level > JSON_MAX_DEPTH
			|| ((t_json_lexeme *)(*lst)->content)->type != TK_OPEN_OBJECT)
		return (NULL);
	token = (t_json_token *)ft_memalloc(sizeof(t_json_token));
	if (token == NULL)
		return (NULL);
	token->type = JSON_OBJECT;
	while (*lst != NULL && (*lst = (*lst)->next) != NULL)
	{
		if (((t_json_lexeme *)(*lst)->content)->type == TK_CLOSE_OBJECT)
			return (token);
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
	return (del_json_token(token));
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
		root = read_json_object(&curr, 1);
	}
	ft_lstdel(&lst, del_json_lexeme);
	return (root);
}
