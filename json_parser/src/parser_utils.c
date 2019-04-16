/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:05:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 12:23:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"
#include "parser.h"

int		check_for_unknown_lexeme_type(t_list *lst)
{
	t_list	*curr;

	if (lst == NULL)
		return (1);
	curr = lst;
	while (curr->next != NULL)
		curr = curr->next;
	return (((t_json_lexeme *)curr->content)->type == TK_UNKNOWN);
}

int		expect_json_sep(t_list **lst, const char *sep)
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

void	*del_json_token(t_json_token *token)
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
