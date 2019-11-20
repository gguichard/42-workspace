/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 22:31:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/11/20 22:49:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "utils.h"

double		clamp(double value, double lo, double hi)
{
	if (value < lo)
		return (lo);
	else if (value > hi)
		return (hi);
	else
		return (value);
}
