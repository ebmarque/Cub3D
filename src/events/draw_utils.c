/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:35:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/18 16:52:57 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bbp / 8));
	*(unsigned int*)dst = color;
}

void	_black_window(t_img *m, float factor)
{
	
	for (int i = 0; i < HEIGHT * factor; i++)
	{
		for (int j = 0; j < WIDTH * factor; j++)
		{
			my_mlx_pixel_put(m, j, i, 0);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

int	_get_reverse(t_rgb	color)
{
	return (255 << 24 | (255 - color.r) << 16 | (255 - color.g) << 8 | ((255 - color.b)));
}

int	_get_reverseb(t_rgb	color)
{
	return (255 << 24 | color.r << 16 | (172 - color.g) << 8 | color.b);
}

void	_draw_square(t_gmap *mini, int x, int y, int factor)
{
	int	i;
	int	j;
	int	color;

	if (factor == 2)
		color = _get_reverseb(cubed()->content->ceiling);
	else
		color = _get_reverse(cubed()->content->ceiling);
	i = -1;
	while (++i < mini->tile / factor)
	{
		j = -1;
		while (++j < mini->tile  / factor)
			my_mlx_pixel_put(&mini->map_img, x + j, y + i, color);
	}
}

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
	//_black_window(&mini->map_img, 0.25f);
	while (++y < cubed()->content->matrix_dimensions.y)
	{
		x = -1;
		while (++x < cubed()->content->matrix_dimensions.x)
		{
			if (mini->map[y][x] == 1)
				_draw_square(mini, x * mini->tile, y * mini->tile, 1);
		}
		
	}
	_draw_player(mini);
	mlx_put_image_to_window(mini->map_img.mlx, \
		mini->map_img.win, mini->map_img.img, 0, 0);
}
