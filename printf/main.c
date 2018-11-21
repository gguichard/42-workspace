/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 23:30:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include "printf.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	setlocale(LC_ALL, "en_US.UTF-8");
	printf("%f\n", 1.42);
	ft_printf("%f\n", 1.42);
	return (0);
}
