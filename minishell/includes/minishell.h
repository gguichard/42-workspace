/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:24:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/01/03 11:19:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_ENV "PATH"

# define NOT_FOUND_ERR -1
# define NOT_REG_ERR -2
# define NOT_DIR_ERR -3
# define NO_EXEC_RIGHTS_ERR -4
# define UNKNOWN_ERR -10

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

void			read_input(t_list **env);

void			process_cmd(char *cmd, t_list **env);

int				is_binary_exec(char *path, int check_dirs);
int				search_for_binary(const char *name, t_list **env, char **path);

char			*get_env(t_list *lst, const char *name, const char *def);
int				set_env(t_list **lst, const char *name, const char *path);
int				unset_env(t_list **lst, const char *name);
char			**get_envtab(t_list *lst);
t_list			*setup_env(char **environ);

void			builtin_cd(int argc, char **argv, t_list **env);
void			builtin_exit(int argc, char **argv, t_list **env);
void			builtin_env(int argc, char **argv, t_list **env);
void			builtin_unsetenv(int argc, char **argv, t_list **env);
void			builtin_setenv(int argc, char **argv, t_list **env);
void			builtin_echo(int argc, char **argv, t_list **env);

char			*expand_str(char *str, t_list **env);

void			free_env(void *content, size_t content_size);
char			*str_error(int err);
char			**env_as_str(t_list **lst);

#endif
