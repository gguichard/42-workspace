/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_network.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:04:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/04 15:44:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "libft.h"
#include "options.h"
#include "fractol.h"
#include "network.h"

static void	init_netdata(t_data *data, t_netdata *netdata)
{
	netdata->type = (int)data->fract_type;
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
	netdata->sampling = data->sampling;
}

static void	read_chunks(int sock, unsigned char *buff, size_t expected)
{
	ssize_t	ret;
	size_t	total;

	total = 0;
	while (total < expected && (ret = read(sock, buff, 4096)) > 0)
	{
		buff += ret;
		total += ret;
	}
}

static void	read_response(t_data *data)
{
	int	size;
	int	*buff;
	int	idx;
	int	buff_idx;

	if (recv(data->network_sock, &size, sizeof(int), MSG_WAITALL) > 0)
	{
		if ((buff = (int *)malloc(size * sizeof(int))) == NULL)
			return ;
		read_chunks(data->network_sock, (unsigned char *)buff
				, size * sizeof(int));
		idx = 0;
		buff_idx = 0;
		while (buff_idx < size)
		{
			while (buff[buff_idx] > 0)
			{
				data->lib.img_data[idx] = buff[buff_idx + 1] * data->color_mul;
				buff[buff_idx] -= 1;
				idx++;
			}
			buff_idx += 2;
		}
		free(buff);
	}
}

int			setup_network(t_data *data)
{
	struct sockaddr_in	srv;

	data->network_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (data->network_sock < 0)
		return (0);
	srv.sin_addr.s_addr = inet_addr(get_optarg(data->opts, 'n'));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(1103);
	if (connect(data->network_sock, (struct sockaddr *)&srv, sizeof(srv)) < 0)
		return (0);
	else
		return (1);
}

void		draw_network(t_data *data)
{
	t_netdata	netdata;

	init_netdata(data, &netdata);
	write(data->network_sock, &netdata, sizeof(t_netdata));
	read_response(data);
}
