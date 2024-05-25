/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:01:53 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/05 17:01:13 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_inside_y_limits(int y)
{
	int	max;
	max = cubed()->content->matrix_dimensions.y;
	if (y >=0 && y <= max)
		return (true);
	return (false);
}

bool	_inside_x_limits(int x)
{
	int	max;

	max = cubed()->content->matrix_dimensions.x;
	if (x >=0 && x <= max)
		return (true);
	return (false);
}