/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:39:32 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/19 11:57:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "computorv1.h"
#include "lexer.h"
#include "ast.h"
#include "utils.h"

static const op_map_t	ope_map_fn[] = {
	{e_LEX_OPE_PLUS, factor_list_add},
	{e_LEX_OPE_MINUS, factor_list_sub},
	{e_LEX_OPE_MUL, factor_list_mul},
	{e_LEX_OPE_DIV, factor_list_div},
	{e_LEX_OPE_POW, factor_list_pow}
};

static factor_list_t	*create_end_factor(ast_node_t *root)
{
	factor_list_t	*factor = malloc(sizeof(factor_list_t));

	if (factor == NULL)
		exit_unexpected();
	factor->next = NULL;
	if (root->token->type == e_LEX_VAR)
		factor->power = factor->value = 1;
	else
	{
		factor->power = 0;
		factor->value = atof(root->token->content);
	}
	return factor;
}

static void				print_compute_details(ast_node_t *node
	, factor_list_t *factor_lst
	, factor_list_t *left_lst
	, factor_list_t *right_lst)
{
	fprintf(stdout, "(");
	print_factor_list(left_lst);
	fprintf(stdout, ") \e[1m\e[31;1m%.*s\e[0m ("
		, (int)node->token->content_size, node->token->content);
	print_factor_list(right_lst);
	fprintf(stdout, ") = \e[33;1m");
	print_factor_list(factor_lst);
	fprintf(stdout, "\e[0m\n");
	fprintf_char_n_times(stdout, '-', 80);
	fprintf(stdout, "\n");
	print_ast(node);
	fprintf(stdout, "\n");
}

static factor_list_t	*create_factor_list(ast_node_t *node, int print_details)
{
	size_t			idx;
	factor_list_t	*left_lst, *right_lst;
	factor_list_t	*factor_lst = NULL;

	for (idx = 0; idx < (sizeof(ope_map_fn) / sizeof(ope_map_fn[0])); idx++)
	{
		if (ope_map_fn[idx].type == node->token->type)
		{
			left_lst = ast_factor_list(node->left, print_details);
			right_lst = ast_factor_list(node->right, print_details);
			factor_lst = ope_map_fn[idx].fn(left_lst, right_lst);
			if (factor_lst != NULL && print_details)
				print_compute_details(node, factor_lst, left_lst, right_lst);
			free_factor_list(&left_lst);
			free_factor_list(&right_lst);
			break;
		}
	}
	return factor_lst;
}

factor_list_t			*ast_factor_list(ast_node_t *root, int print_details)
{
	factor_list_t	*factor_lst = NULL;

	if (root == NULL)
		return NULL;
	switch (root->token->type)
	{
		case e_LEX_NUMBER:
		case e_LEX_VAR:
			factor_lst = create_end_factor(root);
			break;
		case e_LEX_OPE_PLUS:
		case e_LEX_OPE_MINUS:
		case e_LEX_OPE_MUL:
		case e_LEX_OPE_DIV:
		case e_LEX_OPE_POW:
			factor_lst = create_factor_list(root, print_details);
			break;
		default:
			break;
	}
	return factor_lst;
}
