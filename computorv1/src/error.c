/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:15:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 13:14:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "error.h"
#include "lexer.h"

static void	fprintf_char_n_times(FILE *stream, char c, size_t times)
{
	size_t	n;

	for (n = 0; n < times; n++)
		fprintf(stream, "%c", c);
}

static void	print_nodes_for_error(lexeme_list_t *lst, lexeme_t *err_node)
{
	lexeme_t	*node;

	fprintf(stderr, " ");
	for (node = lst->front; node != NULL; node = node->next)
	{
		if (node == err_node)
			fprintf(stderr, "\e[31;1m");
		fprintf(stderr, "%.*s", (int)node->content_size, node->content);
		if (node == err_node)
			fprintf(stderr, "\e[0m");
	}
	fprintf(stderr, "\n ");
	for (node = lst->front; node != NULL; node = node->next)
	{
		if (node != err_node)
			fprintf_char_n_times(stderr, ' ', node->content_size);
		else
		{
			fprintf(stderr, "\e[31;1m~");
			fprintf_char_n_times(stderr, '-', node->content_size - 1);
			fprintf(stderr, "\e[0m");
		}
	}
	fprintf(stderr, "\n");
}

int			print_lexical_errors_if_any(lexeme_list_t *lst)
{
	int			ret = 0;
	lexeme_t	*node;

	for (node = lst->front; node != NULL; node = node->next)
	{
		if (node->type == e_LEX_UNKNOWN)
		{
			ret = 1;
			fprintf(stderr, "\e[37;1msyntax:\e[0m \e[31;1merror:"
				"\e[0m < \e[37;1m%.*s\e[0m > unknown token\n"
				, (int)node->content_size, node->content);
			print_nodes_for_error(lst, node);
		}
	}
	return ret;
}

void		print_parser_error(lexeme_list_t *lst, lexeme_t *err_node
	, const char *info)
{
	fprintf(stderr, "\e[37;1msyntax:\e[0m \e[31;1merror:"
		"\e[0m < \e[37;1m%.*s\e[0m > %s\n"
		, (int)err_node->content_size, err_node->content, info);
	print_nodes_for_error(lst, err_node);
}
