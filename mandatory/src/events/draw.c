/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 19:56:16 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void	_draw_player_square(t_gmap *mini, int center_x, int center_y)
{
	int	size;
	int	x;
	int	y;
	int	i;
	int	j;
	int	color;

	size = mini->tile / 2;
	x = center_x - size / 2;
	y = center_y - size / 2;
	i = 0;
	color = _get_reverseb(cubed()->content->ceiling);
	while (i < size )
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&cubed()->mx_var->screen_buffer, \
				x + j, y + i, color);
			j++;
		}
		i++;
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
		}
	}
	_draw_player(mini);
}
