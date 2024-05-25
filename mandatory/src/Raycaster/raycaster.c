/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:20 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/05/25 19:50:07 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	init_ray(t_ray *ray, int x_cord)
{
	//X coordinate of the camera plane;
	double		x_cam;
	//Struct with data regarding the player;
	t_player	*p;

	p = (cubed()->player);
	x_cam = 2 * (double)x_cord / (double)WIDTH - 1;
	ray->pos = p->pos;
	ray->dir.x = p->dir.x + p->plane.x * x_cam;
	ray->dir.y = p->dir.y + p->plane.y * x_cam;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}
//Gets distance from one x or y side to the next x or y side;
void	get_side_dist(t_ray *ray)
{
	if (ray->dir.x > 0)
	{
		ray->step.x = 1;
		//Colocar o int desta forma permite definir a box na grid;
		//(int)ray->pos.x equivale a mapx;
		ray->side_dist.x = ((int)ray->pos.x + 1 - ray->pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - (int)ray->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = 1;
		ray->side_dist.y = ((int)ray->pos.y + 1 - ray->pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - (int)ray->pos.y) * ray->delta_dist.y;
	}
}

void	perform_dda(t_ray *ray)
{
	bool	hit;

	hit = false;
	while(!hit)
	{
		//jump to next map square, either in x-direction, or in y-direction
        if (ray->side_dist.x < ray->side_dist.y)
        {
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
		//Is sufficient to check the map wall
		if (cubed()->content->map[(int)ray->pos.y][(int)ray->pos.x] > 0)
			hit = true;
	}
}


//changed WIDTH for HEIGHT
void	wall_placement(t_ray *ray)
{
	t_pos	curr;

	curr = cubed()->player->pos;
	if (!ray->side)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->start = HEIGHT/2 - ray->line_height / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	//The value wall_X represents the exact Y value where the wall was hit,
	//not just the integer coordinates of the wall
	if (!ray->side)
		ray->wall_x = curr.y + ray->wall_dist * -ray->dir.y;
	else
		ray->wall_x = curr.x + ray->wall_dist * ray->dir.x;
	//Floor is a C function that returns the largest integer value not greater than x;
	//this allows to get the non integer part of the wall_x;
	ray->wall_x -= floor(ray->wall_x);
}

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

int	shader_texture(double wall_dist, int color)
{
	double	shader;
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

void	texture_render(t_ray *ray, int x_cord)
{
	int	y;
	t_text_info	*text;
	t_texture	*text_info;
	int	color;

	y = ray->start;
	text_info = get_text_info(ray);
	text = ft_calloc(1, sizeof(t_text_info));
	text->x = (ray->wall_x * (double)text_info->width);
	text->step = (double)text_info->height / ray->line_height;
	text->pos = (ray->start - (double)HEIGHT / 2 + (double)ray->line_height / 2 ) * text->step;
	while (y < ray->end)
	{
		text->y = (int)text->pos & (text_info->height - 1);
		text->pos += text->step;
		color = _get_img_pixel(text_info, text->x, text->y);
		render_pixel(x_cord, y, shader_texture(ray->wall_dist, color));
		y++;
	}
}

int	shader_floor(double ref, double wall_dist, int color)
{
	double	shader;
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
	double	shader;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	shader = (ref - wall_dist) / ref;
	r = shader * (color >> 16 & 0xFF);
	g = shader * (color >> 8 & 0xFF);
	b = shader * (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

void	_render_floor(int x)
{
	double y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		render_pixel(x, y, shader_floor(HEIGHT/2 , y, gen_trgb(0, cubed()->content->floor)));
		y++;
	}
}

void	_render_ceiling(int x)
{
	double y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		render_pixel(x, y, shader_ceilling(HEIGHT/2 , y, gen_trgb(0, cubed()->content->ceiling)));
		y++;
	}
}

void	raycaster(void)
{
    t_ray	ray;
    int		x;

    x = 0;
    while(x < WIDTH)
    {
		_render_floor(x);
		_render_ceiling(x);
        init_ray(&ray, x);
		get_side_dist(&ray);
		perform_dda(&ray);
		wall_placement(&ray);
		texture_render(&ray, x);
		x++;
    }
}


int	render_screen(void)
{
	_black_window(&cubed()->mx_var->screen_buffer, 1.0f);
	_raycasting_loop();
	raycaster();
	mlx_put_image_to_window(cubed()->mx_var->mlx, cubed()->mx_var->win, cubed()->mx_var->screen_buffer.img, 0,0);
	return(EXIT_SUCCESS);
}