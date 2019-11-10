/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:51:15 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/10 13:59:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "wolf3d.h"
#include "error.h"

int	main(int argc, char **argv)
{
	t_error	err;
	t_ctx	ctx;

	err = ERR_NOERROR;
	if (argc <= 1)
		err = ERR_USAGE;
	else if (SDL_Init(SDL_INIT_VIDEO) < 0)
		err = ERR_LIBSDL2;
	else
	{
		err = wolf3d_init(&ctx, argv[1]);
		wolf3d_clean(&ctx);
		SDL_Quit();
	}
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "error: %s\n", error_to_str(err));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
