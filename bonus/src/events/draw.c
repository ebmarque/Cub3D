/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/23 16:08:34 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_draw_player(t_gmap *mini)
{
	int	x;
	int	y;

	x = (int)floor(mini->player.x);
	y = (int)floor(mini->player.y);
	_draw_square(mini, x, y, 2);
}

void	_draw_map(t_gmap *mini)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cubed()->content->matrix_dimensions.y)
	{
		x = -1;
		while (++x < cubed()->content->matrix_dimensions.x)
		{
			if (mini->map[y][x] == 1)
				_draw_square(mini, x * mini->tile, y * mini->tile, 1);
			else if (mini->map[y][x] == 'C')
				_draw_square(mini, x * mini->tile, y * mini->tile, 3);
		}
	}
	_draw_player(mini);
	mlx_put_image_to_window(mini->map_img.mlx, \
		mini->map_img.win, mini->map_img.img, 0, 0);
}
