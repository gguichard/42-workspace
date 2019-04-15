/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:24:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 23:47:43 by gguichar         ###   ########.fr       */
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
		ft_printf("PARSING DONE\n");
	while (1) ; // boucle pour checker les leaks
	return (0);
}
