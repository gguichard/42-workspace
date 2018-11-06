/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:23:11 by gguichar          #+#    #+#             */
/*   Updated: 2018/11/05 15:30:48 by gguichar         ###   ########.fr       */
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
