/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:36:59 by tiago             #+#    #+#             */
/*   Updated: 2024/05/28 20:38:06 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_texture	*get_text_info(t_ray *ray)
{
	t_texture	*text;

	if (!ray->side)
	{
		if (ray->dir.x < 0)
			text = cubed()->texture[WEST];
		else
			text = cubed()->texture[EAST];
	}
	else
	{
		if (ray->dir.y < 0)
			text = cubed()->texture[SOUTH];
		else
			text = cubed()->texture[NORTH];
	}
	return (text);
}

void	render_pixel(int x, int y, int color)
{
	char	*dst;
	t_img	img;

	img = cubed()->mx_var->screen_buffer;
	dst = (char *)img.addr + (y * img.line_length + x
			* (img.bbp / 8));
	*(unsigned int *)dst = color;
}

int	_get_img_pixel(t_texture *mlx, int x, int y)
{
	return (*(unsigned int *)(mlx->addr + \
		(y * mlx->line_len) + (x * (mlx->bpp / 8))));
}

void	_render_floor(int x)
{
	double	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		render_pixel(x, y, shader_floor(HEIGHT / 2, y, \
			gen_trgb(0, cubed()->content->floor)));
		y++;
	}
}

void	_render_ceiling(int x)
{
	double	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		render_pixel(x, y, shader_ceilling(HEIGHT / 2, y, \
			gen_trgb(0, cubed()->content->ceiling)));
		y++;
	}
}
