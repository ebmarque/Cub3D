/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:35:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/08 19:39:48 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bbp / 8));
	*(unsigned int*)dst = color;
}

void	_black_window(t_img *m)
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			my_mlx_pixel_put(m, j, i, 0);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

bool	_insede_p_square(int x, int y, int side_l, t_point c)
{
	if (x < 0 || y < 0)
		return (false);
	if (x >= c.x - (int)(side_l / 2) && x <= c.x + (int)(side_l / 2))
	{
		if (y >= c.y - (int)(side_l / 2) && y <= c.y + (int)(side_l / 2))
			return (true);
	}
	return (false);
}

void	_draw_map_square(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = x;
	while (x < i + BLOCK_SIDE)
	{
		j = y;
		while (y < j + BLOCK_SIDE)
		{
			my_mlx_pixel_put(img, x, y, color);
			j++;
		}
		x++;
	}
}
t_point	_get_minimap_beggin(t_player *p, t_gmap *map)
{
	t_point	counter;

	counter.x = (int)round(p->pos.x);
	counter.y = (int)round(p->pos.y);
	return (counter);
}

void	_draw_map(t_player *p, t_gmap *map, t_img *img)
{
	t_point	block;
	int		x_ref;
	block = _get_minimap_beggin(p, map);
	x_ref = block.x;
	while (++block.y < (map->blk_y * 10))
	{
		block.x = x_ref;
		while (++block.x < (map->blk_x * 10))
		{
			if (block.y < 0)
				break ;
			if (block.x < 0)
				continue;
			if (map->map[block.y][block.x] == 1)
				_draw_wall(block.y, block.x, 0xFFFF0000, img);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
