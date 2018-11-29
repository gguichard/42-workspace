/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:25:22 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/29 17:28:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	set_env(t_list **lst, const char *name, const char *value)
{
	t_env	*env;
	t_list	*elem;

	if (!(env = (t_env *)malloc(sizeof(*env))))
		return (NULL);
	env->name = name;
	env->path = path;
}
