/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:09:50 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/05 20:41:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 4096

int		ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
}

int		read_file(char *filename)
{
	int		fd;
	int		size_read;
	char	buffer[BUFF_SIZE];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr("File doesn't exist.\n");
		return (0);
	}
	while ((size_read = read(fd, buffer, BUFF_SIZE)) > 0)
		write(1, buffer, size_read);
	close(fd);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc <= 1)
	{
		ft_puterr("File name missing.\n");
		return (1);
	}
	else if (argc > 2)
	{
		ft_puterr("Too many arguments.\n");
		return (1);
	}
	return (!read_file(argv[1]));
}
