/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 08:26:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "printf.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("%*3d\n", 5, 0);
	ft_printf("%*3d\n", 5, 0);
	return (0);
}
