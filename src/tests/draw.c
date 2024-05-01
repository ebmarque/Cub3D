/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:08:03 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


void	_black_window(t_p *game)
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			my_mlx_pixel_put(game->img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
} 



bool	_is_inside(t_point center, int y, int x, int lengh)
{
	if (x >= center.x - (lengh / 2) && x <= center.x + (lengh / 2))
	{
		if (y >= center.y - (lengh / 2) && y <= center.y + (lengh / 2))
			return true;
	}
	return false;
}


void draw_square(t_p *game, int lengh)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (_is_inside(game->center, y, x, lengh))
				my_mlx_pixel_put(game->img, x, y, 0x00FF0000);
		}
	}
}
