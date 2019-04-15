/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:24:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 18:08:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int					main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*curr;
	t_token	*tok;

	if (argc < 2)
		return (1);
	lst = split_str_into_tokens(argv[1]);
	if (lst == NULL)
		ft_dprintf(STDERR_FILENO, "malloc error\n");
	curr = lst;
	while (curr != NULL)
	{
		tok = (t_token *)curr->content;
		ft_printf("TK{type=\"%s\", value=\"%s\"}\n", get_tk_type(tok->type)
				, tok->value);
		curr = curr->next;
	}
	return (0);
}
