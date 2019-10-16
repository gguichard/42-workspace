/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:41:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/16 16:01:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTORV1_H
# define COMPUTORV1_H

# include "ast.h"
# include "lexer.h"

typedef struct factor_list factor_list_t;

/*
 * POLY SOLVER
 */

void			reorder_poly_factors(factor_list_t **lst);
void			solve_poly(ast_node_t *root);

typedef struct
{
	int		degree;
	void	(*fn)(factor_list_t *);
} solve_map_t;

/*
 * FACTORS
 */

struct factor_list
{
	struct factor_list	*next;
	double				value;
	int					power;
};

typedef struct
{
	lexeme_type_t	type;
	factor_list_t	*(*fn)(factor_list_t *, factor_list_t *);
} op_map_t;

factor_list_t	*ast_factor_list(ast_node_t *root);
int				solve_poly_fn(int degree, factor_list_t *poly);

factor_list_t	*get_factor(factor_list_t *lst, int power);
double			get_factor_value_or_default(factor_list_t *lst
	, int power, double def);
factor_list_t	*get_factor_or_create(factor_list_t **lst, int power);

factor_list_t	*factor_list_derivate(factor_list_t *poly);
void			reduce_factor_list(factor_list_t **lst, factor_list_t *from);
void			free_factor_list(factor_list_t **lst);

factor_list_t	*factor_list_plus(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_minus(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_mul(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_div(factor_list_t *a, factor_list_t *b);
factor_list_t	*factor_list_pow(factor_list_t *a, factor_list_t *b);

#endif
