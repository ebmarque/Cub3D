/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/05 20:33:45 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bbp / 8));
	*(unsigned int*)dst = color;
}

static void	_draw_dir(t_pos p1, t_img *img, double teta)
{
	t_pos	p2;


	p2.x = p1.x - (cos(teta) * 200);
	p2.y = p1.y - (sin(teta) * 200);

	if (p2.x < 0 || p2.x > WIDTH)
	{
		while (p2.x < 0)
			p2.x += 1;
		while (p2.x > WIDTH)
			p2.x -= 1;
				
	}
	if (p2.y < 0 || p2.y > HEIGHT)
	{
		while (p2.y < 0)
			p2.y += 1;
		while (p2.y > HEIGHT)
			p2.y -= 1;
				
	}

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double steps = fmax(fabs(dx), fabs(dy));
    double x_increment = dx / steps;
    double y_increment = dy / steps;

    double x = p1.x;
    double y = p1.y;

    for (int i = 0; i < steps; i++)
	{
		my_mlx_pixel_put(img, (int)(round(x)), (int)(round(y)), 0xFFFFFFFF);
        x += x_increment;
        y += y_increment;
    }
}

void	_black_window(t_mx_var *m)
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			my_mlx_pixel_put(&m->screen_buffer, j, i, 0);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->screen_buffer.img, 0, 0);
} 



static bool	_insede_p_square(t_player *p, int y, int x)
{
	int	px;
	int	py;

	px = (int)(round(p->pos.x));
	py = (int)(round(p->pos.y));
	if (x >= px - 5 && x <= px + 5)
	{
		if (y >= py - 5 && y <= py + 5)
			return true;
	}
	return false;
}

void	_draw_player(t_player *p, t_mx_var *m)
{
	int	i;
	int	j;
	double f;

	f = cubed()->player->dir.teta;
	_draw_dir(p->pos, &m->screen_buffer, f);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (_insede_p_square(p, i, j))
				my_mlx_pixel_put(&m->screen_buffer, j, i, 0xFFFF0000);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->screen_buffer.img, 0, 0);
}