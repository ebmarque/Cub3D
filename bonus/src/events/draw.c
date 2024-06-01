/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/06/01 20:04:52 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void	_draw_player_square(t_gmap *mini, int center_x, int center_y)
{
	int		size;
	int		color;
	t_point	pos;
	t_point	c;

	size = mini->tile / 2;
	pos.x = center_x - size / 2;
	pos.y = center_y - size / 2;
	c.y = 0;
	color = RED_BLOCK;
	while (c.y < size)
	{
		c.x = 0;
		while (c.x < size)
		{
			my_mlx_pixel_put(&cubed()->mx_var->screen_buffer, \
				pos.x + c.x, pos.y + c.y, color);
			c.x++;
		}
		c.y++;
	}
}
static void	_draw_line(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		my_mlx_pixel_put(&cubed()->mx_var->screen_buffer, x1, y1, 0x00FFA500);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	_draw_fov(t_player *p)
{
	t_point	interaction;
	double angle_s;
	int angle_e;
	double size;

	angle_s = p->pos.teta - (30 * 0.0174f);
	angle_e = 0;
	while (angle_e < 60)
	{
		size = 0.9f;
		interaction.y = (int)((sin(angle_s) * -size) + p->pos.y);
		interaction.x = (int)((cos(angle_s) * size) + p->pos.x);
		while (cubed()->gmap->map[interaction.y + 1][interaction.x + 1] != 1 && size < 8.0f)
		{
			interaction.y = (int)((sin(angle_s) * -size) + p->pos.y);
			interaction.x = (int)((cos(angle_s) * size) + p->pos.x);
			size += 0.1f;
		}
		_draw_line(p->pos.x * cubed()->gmap->tile, p->pos.y * cubed()->gmap->tile, \
			interaction.x * cubed()->gmap->tile, interaction.y * cubed()->gmap->tile);
		angle_s += 0.0174f;
		angle_e++;
	}

}

void	_draw_player(t_gmap *mini)
{
	int	x;
	int	y;

	x = (int)floor(mini->player.x);
	y = (int)floor(mini->player.y);
	if (y < (HEIGHT - 5))
		_draw_player_square(mini, x, y);
}

void	_draw_map(t_gmap *mini)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cubed()->content->matrix_dimensions.y \
		&& y * mini->tile < HEIGHT - 5)
	{
		x = -1;
		while (++x < cubed()->content->matrix_dimensions.x)
		{
			if (mini->map[y][x] == 1)
				_draw_square(mini, x * mini->tile, y * mini->tile, 1);
			else if (mini->map[y][x] == 'C')
				_draw_square(mini, x * mini->tile, y * mini->tile, 3);
			else if (mini->map[y][x] == 'O')
				_draw_square(mini, x * mini->tile, y * mini->tile, 2);
			else if (mini->map[y][x] == 0 || _is_player_char(mini->map[y][x]))
				_draw_square(mini, x * mini->tile, y * mini->tile, 0);
			else
				_draw_square(mini, x * mini->tile, y * mini->tile, 4);
		}
	}
	_draw_player(mini);
	_draw_fov(cubed()->player);
}
