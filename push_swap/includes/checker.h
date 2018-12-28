/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:39:09 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/28 16:34:21 by gguichar         ###   ########.fr       */
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
# define VALID_OPT "f:h"
# define HELP_OPT 'h'
# define FILE_OPT 'f'

/*
** CHECKER PART.
*/
int				apply_rots(t_checker *checker);
int				check_lists(t_checker *checker);

/*
** UTILS.
*/
int				show_error(void);
int				show_help(t_opt *opt);

#endif
