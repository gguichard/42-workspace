/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:31:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/08/16 13:34:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "scop.h"
#include "gl_program.h"
#include "winsize.h"
#include "error.h"

int	main(int argc, char **argv)
{
	t_scop	scop;
	t_error	err;

	(void)argc;
	(void)argv;
	ft_memset(&scop, 0, sizeof(t_scop));
	scop.winsize.width = WIN_WIDTH;
	scop.winsize.height = WIN_HEIGHT;
	err = ERR_NOERROR;
	if (!init_mlx(&scop.lib, scop.winsize, "Scop"))
		err = ERR_MLXINIT;
	if (err == ERR_NOERROR)
		err = gl_create_program(&scop.gl_program, "scop.vertexshader"
			, "scop.fragmentshader");
	if (err != ERR_NOERROR)
	{
		ft_printf("error: %s\n", error_to_str(err));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(scop.lib.mlx_ptr, loop_hook, &scop);
	mlx_expose_hook(scop.lib.win_ptr, expose_hook, &scop);
	mlx_hook(scop.lib.win_ptr, 17, (1L << 17), exit_window, &scop);
	mlx_loop(scop.lib.mlx_ptr);
	return (EXIT_SUCCESS);
}
