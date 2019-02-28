/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:43:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 17:04:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fractol.h"
#include "server.h"

int	init_server(t_server *srv)
{
	srv->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (srv->fd < 0)
		return (-1);
	ft_printf("Socket created with fd %d\n", srv->fd);
	srv->addr.sin_family = AF_INET;
	srv->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv->addr.sin_port = htons(SERVER_PORT);
	if (bind(srv->fd, (struct sockaddr *)&srv->addr, sizeof(srv->addr)) < 0)
		return (-1);
	ft_printf("Server binded on port %d\n", SERVER_PORT);
	if (listen(srv->fd, 1))
		return (-1);
	ft_printf("Waiting for connections...\n");
	return (0);
}

int	accept_client(t_server *srv)
{
	int					socket;
	struct sockaddr_in	addr;
	int					socklen;

	socket = accept(srv->fd, (struct sockaddr *)&addr, (socklen_t *)&socklen);
	if (socket < 0)
		return (-1);
	ft_printf("Client connected\n");
	return (socket);
}
