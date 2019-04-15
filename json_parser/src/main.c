/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:24:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/15 16:19:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "token.h"

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*curr;
	t_token	*tok;

	if (argc < 2)
		return (1);
	lst = split_str_into_tokens(argv[1]);
	if (lst == NULL)
		ft_dprintf(STDERR_FILENO, "malloc error\n");
	curr = lst;
	while (curr != NULL)
	{
		tok = (t_token *)curr->content;
		ft_printf("TK{type=%d, value=\"%s\"}\n", tok->type, tok->value);
		curr = curr->next;
	}
	return (0);
}
