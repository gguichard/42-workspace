/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:39:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/21 10:00:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"
# include "options.h"

typedef struct	s_checker
{
	int			argc;
	char		**argv;
	int			fd;
	t_list		*a;
	t_list		*b;
}				t_checker;

/*
** OPTIONS.
*/
# define VALID_OPT "f:hv"
# define HELP_OPT 'h'
# define FILE_OPT 'f'
# define VERB_OPT 'v'

/*
** PARSING.
*/
int				create_list(t_list **lst, int argc, char **argv);

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

/*
** UTILS.
*/
int				show_error(void);
int				show_help(t_opt *opt);

#endif
