/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:35:05 by tiago             #+#    #+#             */
/*   Updated: 2024/05/29 00:39:14 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	shader_texture(double wall_dist, int color)
{
	double				shader;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	if (wall_dist >= SHADER_DIST)
		return ((0 << 16) | (0 << 8) | 0);
	shader = (SHADER_DIST - wall_dist) / SHADER_DIST;
	r = shader * (color >> 16 & 0xFF);
	g = shader * (color >> 8 & 0xFF);
	b = shader * (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

int	shader_floor(double ref, double wall_dist, int color)
{
	double				shader;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	shader = (wall_dist - ref) / ref;
	r = shader * (color >> 16 & 0xFF);
	g = shader * (color >> 8 & 0xFF);
	b = shader * (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

int	shader_ceilling(double ref, double wall_dist, int color)
{
	double				shader;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	shader = (ref - wall_dist) / ref;
	r = shader * (color >> 16 & 0xFF);
	g = shader * (color >> 8 & 0xFF);
	b = shader * (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

void	texture_render(t_ray *ray, int x_cord)
{
	int			y;
	int			color;
	t_text_info	*text;
	t_texture	*text_info;

	y = ray->start;
	text_info = get_text_info(ray);
	text = ft_calloc(1, sizeof(t_text_info));
	text->x = (ray->wall_x * (double)text_info->width);
	text->step = (double)text_info->height / ray->line_height;
	text->pos = (ray->start - (double)HEIGHT / 2 + \
		(double)ray->line_height / 2) * text->step;
	while (y < ray->end)
	{
		text->y = (int)text->pos & (text_info->height - 1);
		text->pos += text->step;
		color = _get_img_pixel(text_info, text->x, text->y);
		render_pixel(x_cord, y, shader_texture(ray->wall_dist, color));
		y++;
	}
	free(text);
}
