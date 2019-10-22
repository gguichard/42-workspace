/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:31:34 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/22 20:10:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "scop.h"
#include "window.h"
#include "error.h"

int			main(int argc, char **argv)
{
	t_scop	scop;
	t_error	err;

	(void)argc;
	(void)argv;
	ft_memset(&scop, 0, sizeof(t_scop));
	scop.win_data.title = WIN_TITLE;
	scop.win_data.size.width = WIN_WIDTH;
	scop.win_data.size.height = WIN_HEIGHT;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		err = ERR_SDLINIT;
	else
		err = create_context_window(&scop.win_data);
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "error: %s\n", error_to_str(err));
		return (EXIT_FAILURE);
	}
	run_window_loop(&scop.win_data);
	return (EXIT_SUCCESS);
}
