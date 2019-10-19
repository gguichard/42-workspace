/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:40:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/18 11:54:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include "computorv1.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "error.h"

static int	parse_opts(int argc, char **argv)
{
	int	opt;
	int	options = 0;

	while ((opt = getopt(argc, argv, "d")) != -1)
	{
		switch (opt)
		{
			case 'd':
				options |= DEBUG_OPT;
				break;
			default:
				return -1;
		}
	}
	return options;
}

int			main(int argc, char **argv)
{
	int				options;
	lexeme_list_t	lst;
	ast_node_t		*root;

	options = parse_opts(argc, argv);
	if (options == -1 || optind >= argc)
	{
		fprintf(stderr, "usage: %s [-d] poly\n", argv[0]);
		return EXIT_FAILURE;
	}
	lst = split_input_in_lexemes(argv[optind]);
	if (!print_lexical_errors_if_any(&lst))
	{
		root = parse_lexemes(&lst);
		if (root != NULL)
		{
			solve_poly(root, options & DEBUG_OPT);
			free_ast(root);
		}
	}
	free_lexeme_list(&lst);
	return EXIT_SUCCESS;
}
