/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 23:23:51 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 23:25:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "fractol.h"

char	*read_sourcecode(void)
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
