/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:41:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/15 18:21:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTORV1_H
# define COMPUTORV1_H

# include "ast.h"
# include "lexer.h"

/*
 * POLY SOLVER
 */
void			solve_poly(ast_node_t *root);

/*
 * FACTORS
 */

typedef struct factor_list
{
	struct factor_list	*next;
	double				value;
	int					power;
} factor_list_t;

typedef struct
{
	lexeme_type_t	type;
	factor_list_t	*(*fn)(factor_list_t *, factor_list_t *);
} op_map_t;

factor_list_t	*compute_ast_factors(ast_node_t *root);

factor_list_t	*get_factor(factor_list_t *lst, int power);
double			get_factor_value_or_default(factor_list_t *lst
	, int power, double def);
factor_list_t	*get_factor_or_create(factor_list_t **lst, int power);

void			reduce_factor_list(factor_list_t **lst, factor_list_t *from);
void			free_factor_list(factor_list_t **lst);

factor_list_t	*factor_list_plus(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_minus(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_mul(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_div(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_pow(factor_list_t *a, factor_list_t *b);

/*
 * UTILS
 */

double			pow_fn(double nb, int pow);
void			print_value(double value);
void			print_factors(factor_list_t *lst);

#endif
