/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:43:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 22:44:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "token.h"

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
		ft_printf("TK{type=\"%s\", value=\"%s\"}\n", get_tk_type(tok->type)
				, tok->value);
		curr = curr->next;
	}
}
