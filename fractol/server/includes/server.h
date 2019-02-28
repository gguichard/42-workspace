/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:25:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 16:37:01 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include "fractol.h"

# define SERVER_PORT 1103

typedef struct s_server	t_server;

struct s_server
{
	int					fd;
	struct sockaddr_in	addr;
};

int	init_server(t_server *srv);
int	accept_client(t_server *srv);

#endif
