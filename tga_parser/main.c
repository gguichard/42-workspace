/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:26:07 by gguichar          #+#    #+#             */
/*   Updated: 2019/07/31 17:31:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tga_parser.h"

int	main(int argc, char **argv)
{
	t_tga_error	err;
	t_tga_image	tga_image;

	if (argc != 2)
	{
		fprintf(stderr, "missing file name\n");
		return (EXIT_FAILURE);
	}
	err = load_tga_file(argv[1], &tga_image);
	if (err != TGAERR_NOERROR)
		fprintf(stderr, "unable to load %s (error=%d)\n", argv[1], err);
	else
	{
		fprintf(stdout, "%s\nwidth: %hu | height: %hu\n", argv[1]
			, tga_image.width, tga_image.height);
	}
	return (EXIT_SUCCESS);
}
