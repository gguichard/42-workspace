/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:26:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 23:31:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "fractol.h"
#include "server.h"

static void	write_in_chunks(int client, t_data *data
		, const unsigned char *buffer)
{
	int	size;
	int	offset;
	int	len;

	size = data->width * data->height * sizeof(int);
	offset = 0;
	while (size > 0)
	{
		len = ft_min(4096, size);
		write(client, buffer + offset, len);
		size -= len;
		offset += len;
	}
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
		write_in_chunks(client, &data, (unsigned char *)buffer);
		ft_printf("Data sent!\n");
		free(buffer);
	}
	ft_printf("Client connection closed\n");
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
		while ((client = accept_client(&srv)) >= 0)
			client_loop(client, source);
		if (client < 0)
			ft_dprintf(2, "error: %s\n", strerror(errno));
		close(srv.fd);
		ft_printf("Closed server\n");
	}
	free(source);
	return (0);
}
