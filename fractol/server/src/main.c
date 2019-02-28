/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:26:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 14:42:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fractol.h"

static char	*read_sourcecode(void)
{
	int		fd;
	int		ret;
	char	*source;

	fd = open("src/kernel.cl", O_RDONLY);
	if (fd < 0)
		return (NULL);
	source = (char *)malloc(sizeof(char) * (OPENCL_SOURCE + 1));
	if (source == NULL)
		return (NULL);
	ret = read(fd, source, OPENCL_SOURCE);
	if (ret >= 0)
		source[ret] = '\0';
	else
	{
		free(source);
		source = NULL;
	}
	close(fd);
	return (source);
}

int			main(int argc, char **argv)
{
	char	*source;

	(void)argc;
	(void)argv;
	source = read_sourcecode();
	if (source == NULL)
		return (1);
	free(source);
	return (0);
}
