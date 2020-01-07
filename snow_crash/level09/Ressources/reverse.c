/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:08:19 by gguichar          #+#    #+#             */
/*   Updated: 2020/01/06 13:56:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int	main(void)
{
	int				fd;
	struct stat		buf;
	void			*map;
	unsigned char	*str;
	size_t			i;

	fd = open("token", O_RDONLY);
	if (fd == -1 || fstat(fd, &buf) == -1)
		goto error;
	map = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FILE
		, fd, 0);
	if (map == MAP_FAILED)
		goto error;
	str = (unsigned char *)map;
	i = 0;
	while (i < buf.st_size && str[i] != '\n')
	{
		str[i] -= i;
		i++;
	}
	fprintf(stdout, "Password is %s", str);
	munmap(map, buf.st_size);
	return (0);

error:
	if (fd != -1)
		close(fd);
	fprintf(stderr, "got error: %s\n", strerror(errno));
	return (1);
}
