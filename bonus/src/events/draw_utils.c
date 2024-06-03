/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:35:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/06/03 14:32:32 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bbp / 8));
	*(unsigned int *)dst = color;
}

void	_black_window(t_img *m, float factor)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT * factor)
	{
		j = 0;
		while (j < WIDTH * factor)
		{
			my_mlx_pixel_put(m, j, i, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

int	_get_reverse(t_rgb	color)
{
	return (0 << 24 | (255 - color.r) << 16 \
		| (255 - color.g) << 8 | ((255 - color.b)));
}

int	_get_reverseb(t_rgb	color)
{
	return (0 << 24 | color.r << 16 | (172 - color.g) << 8 | color.b);
}


void	_draw_square(t_gmap *mini, int x, int y, int factor)
{
	int	i;
	int	j;
	int	color;

	if (factor == 0)
		color = 0x00000000;
	else if (factor == 1)
		color = 0x0000FF00;
	else if (factor == 2)
		color = 0x00800080;
	else if (factor == 3)
		color = 0x00FFaF5F;
	else
		color = 0x00000000;
	i = -1;
	while (++i < mini->tile - 1)
	{
		j = -1;
		while (++j < mini->tile - 1)
		my_mlx_pixel_put(&cubed()->mx_var->screen_buffer, \
		x + j, y + i, color);
	}
}
