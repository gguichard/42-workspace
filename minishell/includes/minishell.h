/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:24:49 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 13:56:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_ENV "PATH"

# include "libft.h"

typedef struct	s_cmd
{
	char		*name;
	void		(*exec)(int argc, char **argv, t_list **env);
}				t_cmd;

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

void			show_prompt(t_list **env);

char			*get_env(t_list *lst, const char *name);

int				set_env(t_list **lst, const char *name, const char *path);

int				unset_env(t_list **lst, const char *name);

char			**env_as_str(t_list **lst);

t_list			*setup_env(void);

char			*search_for_binary(const char *name, t_list **env);

void			builtin_cd(int argc, char **argv, t_list **env);

void			builtin_exit(int argc, char **argv, t_list **env);

void			builtin_env(int argc, char **argv, t_list **env);

void			builtin_unsetenv(int argc, char **argv, t_list **env);

void			builtin_setenv(int argc, char **argv, t_list **env);

#endif
