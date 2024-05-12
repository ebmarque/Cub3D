/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:35:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/12 16:02:02 by ebmarque         ###   ########.fr       */
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

	i = y;
	j = x;
	int	block_y = (int)round(((HEIGHT / cubed()->content->matrix_dimensions.y)));
	int	block_x = (int)round(((WIDTH / cubed()->content->matrix_dimensions.x)));
	while (y < i + block_y)
	{
		x = j;
		while (x < j + block_x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	_draw_p_square(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = y;
	j = x;
	int	block_y = (int)round(((HEIGHT / cubed()->content->matrix_dimensions.y) * 0.98));
	int	block_x = (int)round(((WIDTH / cubed()->content->matrix_dimensions.x) * 0.98));
	while (y < i + block_y)
	{
		x = j;
		while (x < j + block_x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	_draw_player(t_player *p, t_file *t, t_img *img)
{
	int	y;
	int	x;

	y = (int)(round(p->pos.y));
	x = (int)(round(p->pos.x));
	int	block_y = (int)round(((HEIGHT / cubed()->content->matrix_dimensions.y)));
	int	block_x = (int)round(((WIDTH / cubed()->content->matrix_dimensions.x)));
	(void)t;
	/* if (x + P_SIZE > WIDTH \
		|| y + P_SIZE > HEIGHT)
		return ; */
	_draw_p_square(img, x * block_x, y * block_y, 0xFFFF00FF);
}

void	_draw_map(t_file *t, t_img *img)
{
	int	y;
	int	x;
	int	block_y = (int)round(((HEIGHT / cubed()->content->matrix_dimensions.y)));
	int	block_x = (int)round(((WIDTH / cubed()->content->matrix_dimensions.x)));

	y = -1;
	_black_window(img);
	while (++y < t->matrix_dimensions.y)
	{
		x = -1;
		while (++x < t->matrix_dimensions.x)
		{
			if (t->map[y][x] == 1)
				_draw_map_square(img, x * block_x, y * block_y, RED_BLOCK);
			else if (t->map[y][x] == 0)
				_draw_map_square(img, x * block_x, y * block_y, WHITE_BLOCK);
		}
	}
	_draw_player(cubed()->player, t, img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
