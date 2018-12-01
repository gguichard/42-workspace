/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:34:38 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/01 14:06:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "minishell.h"

static void	print_env(t_list **env)
{
	t_list	*lst;

	lst = *env;
	while (lst != NULL)
	{
		ft_printf("%s=%s\n"
				, ((t_env *)(lst->content))->name
				, ((t_env *)(lst->content))->value);
		lst = lst->next;
	}
}

void		builtin_env(int argc, char **argv, t_list **env)
{
	(void)argc;
	(void)argv;
	print_env(env);
}

void		builtin_setenv(int argc, char **argv, t_list **env)
{
	char	**parts;
	char	*value;

	if (argc <= 1)
	{
		print_env(env);
		return ;
	}
	parts = NULL;
	if (!(parts = ft_strsplit(argv[1], '=')) || !(parts[0]))
	{
		ft_strtab_free(parts);
		ft_dprintf(2, "%s: Invalid name.\n", argv[0]);
		return ;
	}
	if (parts[1] != NULL)
		value = parts[1];
	else
		value = (argc >= 3) ? argv[2] : "0";
	if (!set_env(env, parts[0], value))
		ft_dprintf(2, "%s: Unable to set var value.\n", argv[0]);
	else
		ft_printf("%s: Set to \"%s\".\n", parts[0], value);
	ft_strtab_free(parts);
}

void		builtin_unsetenv(int argc, char **argv, t_list **env)
{
	int	index;

	if (argc <= 1)
	{
		ft_dprintf(2, "%s: Missing name.\n", argv[0]);
		return ;
	}
	index = 1;
	while (index < argc)
	{
		if (!(unset_env(env, argv[index])))
		{
			ft_dprintf(2, "%s: Not a valid name.\n", argv[index]);
			return ;
		}
		ft_printf("%s: Has been removed.\n", argv[index]);
		index++;
	}
}
