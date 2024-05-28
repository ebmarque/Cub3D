/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:31:56 by tiago             #+#    #+#             */
/*   Updated: 2024/05/28 21:43:26 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	init_ray(t_ray *ray, int x_cord)
{
	double		x_cam;
	t_player	*p;

	p = (cubed()->player);
	x_cam = 2 * (double)x_cord / (double)WIDTH - 1;
	ray->pos = p->pos;
	ray->dir.x = p->dir.x + p->plane.x * x_cam;
	ray->dir.y = p->dir.y + p->plane.y * x_cam;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	get_side_dist(t_ray *ray)
{
	if (ray->dir.x > 0)
	{
		ray->step.x = 1;
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
	while (!hit)
	{
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
		if (_wall_char(cubed()->content->map[(int)ray->pos.y][(int)ray->pos.x]))
			hit = true;
	}
}

void	wall_placement(t_ray *ray)
{
	t_pos	curr;

	curr = cubed()->player->pos;
	if (!ray->side)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->start = HEIGHT / 2 - ray->line_height / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	if (!ray->side)
		ray->wall_x = curr.y + ray->wall_dist * -ray->dir.y;
	else
		ray->wall_x = curr.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
