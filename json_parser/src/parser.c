/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:09:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 18:07:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"

void			*del_json_token(t_json_token *token)
{
	free(token->key);
	if (token->type == JSON_STRING)
		free(token->value.str);
	else if (token->type == JSON_ARRAY || token->type == JSON_OBJECT)
		del_json_token_childs(token);
	free(token);
	return (NULL);
}

void			del_json_token_childs(t_json_token *token)
{
	t_json_token	*curr;
	t_json_token	*next;

	curr = token->value.child;
	while (curr != NULL)
	{
		next = curr->next;
		del_json_token(curr);
		curr = next;
	}
	token->value.child = NULL;
}

t_json_token	*eat_json_lexemes(t_list **lst, int depth_level)
{
	t_json_token	*token;
	t_json_lexeme	*lexeme;

	if (depth_level > JSON_MAX_DEPTH
			|| !(token = (t_json_token *)ft_memalloc(sizeof(t_json_token))))
		return (NULL);
	lexeme = (t_json_lexeme *)(*lst)->content;
	if (lexeme->type == TK_STRING)
		read_json_string(lexeme, token);
	else if (lexeme->type == TK_NUMBER)
		read_json_number(lexeme, token);
	else if (lexeme->type == TK_PRIMITIVE)
		read_json_primitive(lexeme, token);
	else if (lexeme->type == TK_OPEN_OBJECT || lexeme->type == TK_OPEN_ARRAY)
	{
		*lst = (*lst)->next;
		if (read_json_object_or_array(lst, depth_level + 1, token
					, lexeme->type == TK_OPEN_OBJECT))
			token->type = (lexeme->type == TK_OPEN_OBJECT
					? JSON_OBJECT : JSON_ARRAY);
	}
	if (token->type == JSON_UNKNOWN)
		return (del_json_token(token));
	*lst = (*lst)->next;
	return (token);
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
		if (root != NULL && curr != NULL)
			root = del_json_token(root);
	}
	ft_lstdel(&lst, del_json_lexeme);
	return (root);
}
