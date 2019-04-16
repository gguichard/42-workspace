/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:43:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 12:17:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "token.h"
#include "parser.h"

static const char	*get_tk_type(int type)
{
	if (type == TK_STRING)
		return ("STRING");
	else if (type == TK_OPEN_OBJECT)
		return ("OBJ_OPEN");
	else if (type == TK_CLOSE_OBJECT)
		return ("OBJ_CLOSE");
	else if (type == TK_OPEN_ARRAY)
		return ("ARR_OPEN");
	else if (type == TK_CLOSE_ARRAY)
		return ("ARR_CLOSE");
	else if (type == TK_NUMBER)
		return ("NUMBER");
	else if (type == TK_PRIMITIVE)
		return ("PRIMITIVE");
	else if (type == TK_SEPARATOR)
		return ("SEPARATOR");
	else
		return ("UNKNOWN");
}

void				debug_lexemes(t_list *lst)
{
	t_list			*curr;
	t_json_lexeme	*tok;

	if (lst == NULL)
		ft_dprintf(STDERR_FILENO, "malloc error\n");
	curr = lst;
	while (curr != NULL)
	{
		tok = (t_json_lexeme *)curr->content;
		printf("TK{type=\"%s\", value=\"%s\"}\n", get_tk_type(tok->type)
				, tok->value);
		curr = curr->next;
	}
}

void				debug_tokens(t_json_token *token, int tab)
{
	int	i;

	if (token == NULL)
		return ;
	i = 0;
	while (i < tab)
	{
		ft_putchar(' ');
		i++;
	}
	if (token->key != NULL)
		printf("\"%s\": ", token->key);
	if (token->type == JSON_OBJECT)
	{
		printf("{\n");
		debug_tokens(token->value.child, tab + 4);
		i = 0;
		while (i < tab)
		{
			ft_putchar(' ');
			i++;
		}
		printf("}");
	}
	if (token->type == JSON_ARRAY)
	{
		printf("[\n");
		debug_tokens(token->value.child, tab + 4);
		i = 0;
		while (i < tab)
		{
			ft_putchar(' ');
			i++;
		}
		printf("]");
	}
	else if (token->type == JSON_STRING)
		printf("\"%s\"", token->value.str);
	else if (token->type == JSON_BOOLEAN)
		printf("%s", token->value.i ? "true" : "false");
	else if (token->type == JSON_INTEGER)
		printf("%d", token->value.i);
	else if (token->type == JSON_FLOAT)
	{
		printf("%f", token->value.f);
	}
	else if (token->type == JSON_NULL)
		printf("null");
	printf("%s", (token->next != NULL ? ",\n" : "\n"));
	debug_tokens(token->next, tab);
}
