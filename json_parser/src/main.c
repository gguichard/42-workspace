/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:24:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 12:53:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	main(int argc, char **argv)
{
	t_json_token	*root;

	if (argc < 2)
		return (1);
	root = parse_json(argv[1]);
	if (root != NULL)
	{
		ft_printf("PARSING DONE\n");
		debug_tokens(root, 0);
		del_json_token(root);
	}
	return (0);
}
