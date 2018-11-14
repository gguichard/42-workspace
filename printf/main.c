/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:26:21 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/14 16:41:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("je suis un %s allo %d\n", "test", 42);
	return (0);
}
