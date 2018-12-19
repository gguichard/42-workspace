/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:39:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 00:41:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

typedef struct	s_checker
{
	int			argc;
	char		**argv;
	int			options;
	char		*file;
	int			fd;
	t_list		*a;
	t_list		*b;
}				t_checker;

/*
** OPTIONS.
*/
# define VALID_OPT "fhv"
# define HELP_OPT (1 << 7)
# define FILE_OPT (1 << 5)
# define VERB_OPT (1 << 21)

int				parse_options(t_checker *checker);

/*
** PARSING.
*/
t_list			*create_list(t_checker *checker);

/*
** CHECKER PART.
*/
int				apply_sets(t_checker *checker);
int				check_lists(t_checker *checker);

/*
** INSTRUCTIONS.
*/
int				swap(t_list **lst);
int				push(t_list **to, t_list **from);
int				rotate(t_list **lst);
int				rev_rotate(t_list **lst);

#endif
