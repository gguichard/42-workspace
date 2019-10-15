/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:40:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 15:12:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "computorv1.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "error.h"

int	main(int argc, char **argv)
{
	lexeme_list_t	lst;
	ast_node_t		*root;

	if (argc != 2)
	{
		fprintf(stderr, "Nothing to solve.\nusage: %s <poly>\n", argv[0]);
		return EXIT_FAILURE;
	}
	lst = split_input_in_lexemes(argv[1]);
	if (!print_lexical_errors_if_any(&lst))
	{
		root = parse_lexemes(&lst);
		if (root != NULL)
		{
			solve_poly(root);
			free_ast(root);
		}
		free_lexeme_list(&lst);
	}
	return EXIT_SUCCESS;
}
