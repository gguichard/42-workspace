/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_network.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:04:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 18:02:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "libft.h"
#include "fractol.h"

struct	s_netdata
{
	int		type;
	int		width;
	int		height;
	int		x_off;
	int		y_off;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	motion_x;
	double	motion_y;
	int		max_iters;
};

static void	read_chunks(int sock, unsigned char *buff)
{
	ssize_t	ret;
	size_t	total;

	total = 0;
	while ((ret = recv(sock, buff, 4096, 0)) > 0)
	{
		buff += ret;
		total += ret;
		if (total == 4915200)
			break ;
	}
	ft_printf("%zu bytes read\n", total);
}

void		draw_network(t_data *data)
{
	static int			sock = -1;
	struct sockaddr_in	srv;
	struct s_netdata	netdata;

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
	netdata.type = 3;
	netdata.width = data->winsize.width;
	netdata.height = data->winsize.height;
	netdata.x_off = data->cam.x_off;
	netdata.y_off = data->cam.y_off;
	netdata.x_min = data->cam.x_min;
	netdata.x_max = data->cam.x_max;
	netdata.y_min = data->cam.y_min;
	netdata.y_max = data->cam.y_max;
	netdata.motion_x = data->motion.x;
	netdata.motion_y = data->motion.y;
	netdata.max_iters = data->max_iters;
	send(sock, &netdata, sizeof(struct s_netdata), 0);
	read_chunks(sock, (unsigned char *)data->lib.img_data);
}
