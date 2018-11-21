/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:32:56 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/21 16:00:48 by gguichar         ###   ########.fr       */
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
	printf("%.4S\n", L"我是一只猫。");
	ft_printf("%.4S\n", L"我是一只猫。");
	return (0);
}
