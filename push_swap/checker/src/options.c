/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:39:28 by gguichar          #+#    #+#             */
/*   Updated: 2018/12/20 12:40:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	option_mask(char c)
{
	return (1 << (c - 'a'));
}

int			parse_options(t_checker *checker)
{
	int	offset;

	while (checker->argc > 0)
	{
		if (checker->argv[0][0] != '-')
			break ;
		offset = 1;
		while (checker->argv[0][offset] != '\0')
		{
			if (!ft_strchr(VALID_OPT, checker->argv[0][offset]))
				return (0);
			checker->options |= option_mask(checker->argv[0][offset]);
			offset++;
		}
		checker->argc--;
		checker->argv++;
	}
	return (1);
}
