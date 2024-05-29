/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 20:33:04 by ebmarque         ###   ########.fr       */
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
	color = _get_reverseb(cubed()->content->ceiling);
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
		}
	}
	_draw_player(mini);
}
