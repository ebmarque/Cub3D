/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:20 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/04/25 21:34:16 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_ray(t_ray *ray, int x_cord)
{
	//X coordinate of the camera plane;
	double		x_cam;
	//Struct with data regarding the player;
	t_player	p;

	p = /*******/;
	x_cam = 2 * x_cord / (double)SCREEN_W - 1;
	ray->pos = p.pos;
	ray->dir.x = p.dir.x + p.plane.x * x_cam;
	ray->dir.y = p.dir.y + p.plane.y * x_cam;
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
	if (ray->dir.y > 0)
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
		//Is sufficient to check the map wall?
		if (worldMap[(int)ray->pos.x][(int)ray->pos.y] > 0)
			hit = true;
	}
}

void	wall_placement(t_ray *ray)
{
	t_pos	curr;

	curr = /*Player position*/
	if (!ray->side)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
	ray->line_height = (int)(SCREEN_H / ray->wall_dist);
	ray->start = -ray->line_height / 2 + SCREEN_H / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + SCREEN_H / 2;
	if (ray->end >= SCREEN_H)
		ray->end = SCREEN_H - 1;
	//The value wall_X represents the exact Y value where the wall was hit,
	//not just the integer coordinates of the wall
	if (!ray->side)
		ray->wall_x = curr.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = curr.x + ray->wall_dist * ray->dir.x;
}

void	raycaster(void)
{
    t_ray	ray;
    int		x;

    x = 0;
    while(x < SCREEN_W)
    {
        init_ray(&ray, x);
		get_side_dist(&ray);
		perform_dda(&ray);
		wall_placement(&ray);
		/*render texture*/
		x++;
    }
}