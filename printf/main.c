/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/16 15:37:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*str = "ok";
	short test = -129;
	printf("%u test\n", test);
	ft_printf("%u test\n", test);
	return (0);
}
