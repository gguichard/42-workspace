/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:43:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 14:57:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include "libft.h"

int	init_server()
{
	int					fd;
	struct sockaddr_in	addr;

	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		ft_dprintf(2, "fractol: socket: %s\n", strerror(errno));
		return (0);
	}
	ft_memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	if (bind(fd, &addr, sizeof(addr)) < 0)
	{
		close(fd);
		ft_dprintf(2, "fractol: bind: %s\n", strerror(errno));
		return (0);
	}
	return (1);
}
