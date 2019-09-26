/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:18:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/09/26 22:46:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ssl.h"
#include "ft_ssl_md5.h"

int	main(int argc, char **argv)
{
	if (argc > 1)
		md5_hash((uint8_t *)argv[1], ft_strlen(argv[1]));
	return (EXIT_SUCCESS);
}
