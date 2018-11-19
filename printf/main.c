/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/20 00:08:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"

int	main(int argc, char **argv)
{
	float	test = -118.1284983505;

	(void)argc;
	(void)argv;
	printf("%.100f\n", test);
	ft_printf("%.100f\n", test);
	return (0);
}
