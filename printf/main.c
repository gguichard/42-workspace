/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/19 17:56:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"

int	main(int argc, char **argv)
{
	float	test = -118.625;

	(void)argc;
	(void)argv;
	printf("%f\n", test);
	ft_printf("%f\n", test);
	return (0);
}
