/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:25:22 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/28 11:35:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static int	replace_val(t_list *elem, char *value)
{
	char	*tmp;

	tmp = ((t_env *)(elem->content))->value;
	((t_env *)(elem->content))->value = value;
	free(tmp);
	return (1);
}

int			set_env(t_list **lst, const char *name, const char *value)
{
	t_list	*begin;
	t_env	env;
	t_list	*elem;

	if (!(env.value = ft_strdup(value)))
		return (0);
	begin = *lst;
	while (begin != NULL)
	{
		if (ft_strequ(name, ((t_env *)(begin->content))->name))
			return (replace_val(begin, env.value));
		begin = begin->next;
	}
	if (!(env.name = ft_strdup(name))
			|| !(elem = ft_lstnew(&env, sizeof(env))))
	{
		free(env.value);
		free(env.name);
		return (0);
	}
	ft_lstpush(lst, elem);
	return (1);
}

int			unset_env(t_list **lst, const char *name)
{
	t_list	*elem;
	t_list	*prev;

	elem = *lst;
	prev = NULL;
	while (elem != NULL)
	{
		if (ft_strequ(name, ((t_env *)(elem->content))->name))
			break ;
		prev = elem;
		elem = elem->next;
	}
	if (elem == NULL)
		return (0);
	if (prev == NULL)
		*lst = NULL;
	else
		prev->next = elem->next;
	ft_lstdelone(&elem, &free_env);
	return (1);
}

char		*get_env(t_list *lst, const char *name, const char *def)
{
	while (lst != NULL)
	{
		if (ft_strequ(name, ((t_env *)lst->content)->name))
			return (((t_env *)(lst->content))->value);
		lst = lst->next;
	}
	return (char *)(def);
}

t_list		*setup_env(char **environ)
{
	size_t	index;
	char	**parts;
	int		res;
	t_list	*lst;

	index = 0;
	lst = NULL;
	while (environ[index] != NULL)
	{
		res = 0;
		if (!(parts = ft_strsplit(environ[index], '=')))
			return (ft_lstdel(&lst, &free_env));
		res = set_env(&lst, parts[0], parts[1] == NULL ? "" : parts[1]);
		ft_strtab_free(parts);
		if (!res)
			return (ft_lstdel(&lst, &free_env));
		index++;
	}
	return (lst);
}
