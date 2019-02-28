/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:26:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 16:38:06 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "fractol.h"
#include "server.h"

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

static void	client_loop(int client, const char *source)
{
	t_data	data;
	ssize_t	ret;
	int		*buffer;

	while ((ret = recv(client, &data, sizeof(t_data), MSG_WAITALL)) > 0)
	{
		if (ret != sizeof(t_data))
		{
			ft_dprintf(2, "error: Not enough data received\n");
			break ;
		}
		buffer = (int *)malloc(data.width * data.height * sizeof(int));
		if (buffer == NULL)
		{
			ft_dprintf(2, "error: Unexpected error\n");
			break ;
		}
		compute_fractal(&data, source, buffer);
		if (send(client, buffer, data.width * data.height * sizeof(int)
					, MSG_DONTWAIT) < 0)
			ft_dprintf(2, "error: %s\n", strerror(errno));
		free(buffer);
	}
	close(client);
}

int			main(int argc, char **argv)
{
	char		*source;
	t_server	srv;
	int			client;

	(void)argc;
	(void)argv;
	if ((source = read_sourcecode()) == NULL)
	{
		ft_dprintf(2, "error: %s\n", strerror(errno));
		return (1);
	}
	ft_memset(&srv, 0, sizeof(t_server));
	if (init_server(&srv) < 0)
		ft_dprintf(2, "error: %s\n", strerror(errno));
	else
	{
		if ((client = accept_client(&srv)) < 0)
			ft_dprintf(2, "error: %s\n", strerror(errno));
		else
			client_loop(client, source);
		close(srv.fd);
		ft_printf("Closed server\n");
	}
	free(source);
	return (0);
}
