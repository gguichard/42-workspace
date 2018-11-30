/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:25:14 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/30 19:15:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "minishell.h"

int	main(int argc, char **argv, char **environ)
{
	t_list	*env;

	(void)argc;
	(void)argv;
	if (!(env = setup_env(environ)))
	{
		ft_dprintf(2, "minishell: Unable to read environ.\n");
		return (1);
	}
	while (1)
		show_prompt(&env);
	return (0);
}
