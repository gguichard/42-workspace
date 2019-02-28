/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_network.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:04:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 23:33:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "libft.h"
#include "fractol.h"
#include "network.h"

static int	get_fract_type(t_data *data)
{
	if (data->fract_fn == mandelbrot)
		return (1);
	else if (data->fract_fn == mandelbar)
		return (2);
	else if (data->fract_fn == burning_ship)
		return (3);
	else
		return (0);
}

static void	read_chunks(int sock, unsigned char *buff, size_t expected)
{
	ssize_t	ret;
	size_t	total;

	total = 0;
	while (total < expected && (ret = recv(sock, buff, 4096, 0)) > 0)
	{
		buff += ret;
		total += ret;
	}
}

static void	init_netdata(t_data *data, t_netdata *netdata)
{
	netdata->type = get_fract_type(data);
	netdata->width = data->winsize.width;
	netdata->height = data->winsize.height;
	netdata->x_off = data->cam.x_off;
	netdata->y_off = data->cam.y_off;
	netdata->x_min = data->cam.x_min;
	netdata->x_max = data->cam.x_max;
	netdata->y_min = data->cam.y_min;
	netdata->y_max = data->cam.y_max;
	netdata->motion_x = data->motion.x;
	netdata->motion_y = data->motion.y;
	netdata->max_iters = data->max_iters;
}

void		draw_network(t_data *data)
{
	static int			sock = -1;
	struct sockaddr_in	srv;
	t_netdata			netdata;

	if (sock == -1)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0)
			return ;
		srv.sin_addr.s_addr = inet_addr("127.0.0.1");
		srv.sin_family = AF_INET;
		srv.sin_port = htons(1103);
		if (connect(sock, (struct sockaddr *)&srv, sizeof(srv)) < 0)
			return ;
	}
	init_netdata(data, &netdata);
	write(sock, &netdata, sizeof(t_netdata));
	read_chunks(sock, (unsigned char *)data->lib.img_data
			, sizeof(int) * netdata.width * netdata.height);
}
