/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:15:03 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/17 13:39:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "fillit.h"
#include "libft.h"

static int	min_square(int nb)
{
	if (nb <= 3)
		return (nb + 1);
	if (nb <= 4)
		return (4);
	if (nb <= 6)
		return (5);
	if (nb <= 9)
		return (6);
	if (nb <= 12)
		return (7);
	if (nb <= 16)
		return (8);
	if (nb <= 20)
		return (9);
	if (nb <= 25)
		return (10);
	if (nb <= 26)
		return (11);
	return (2);
}

static void	free_shapes(t_info *info)
{
	int	index;

	index = 0;
	while (info->shapes[index] != NULL)
	{
		free(info->shapes[index]);
		index++;
	}
	free(info->shapes);
}

static void	init_board(t_info *info)
{
	int	row;

	row = 0;
	while (row < 16)
	{
		info->board[row] = 0;
		row++;
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_info	info;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit filename");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_exiterror();
	info.shapes = get_shapes(fd);
	close(fd);
	if (info.shapes == NULL)
		ft_exiterror();
	info.count = 0;
	while (info.shapes[info.count] != NULL)
		info.count++;
	info.size = min_square(info.count);
	init_board(&info);
	resolve(&info);
	free_shapes(&info);
	return (0);
}
