/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:23:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/06 08:26:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	n;
	int	result;

	if (nb <= 0)
		return (0);
	n = 0;
	while (n < 46341)
	{
		result = n * n;
		if (result > nb)
			return (0);
		else if (result == nb)
			return (n);
		n++;
	}
	return (0);
}
