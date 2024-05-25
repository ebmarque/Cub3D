/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:05:24 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 22:17:15 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_is_matrix_wall(float ny, float nx)
{
	int	**map;
	int	yu;
	int	xl;
	int	yd;
	int	xr;

	printf("posicao na matrix -> x: %0.3f y: %0.3f\n", cubed()->player->pos.x, cubed()->player->pos.y );
	printf("posicao na screen -> x: %0.3f y: %0.3f\n\n", cubed()->gmap->player.x, cubed()->gmap->player.y );
	yu = (int)(ny);
	yd = (int)(ny + 0.5f);
	xl = (int)(nx);
	xr = (int)(nx + 0.5f);
	map = cubed()->content->map;
	if (map[yu][xl] == 1 || map[yu][xr] == 1 || map[yd][xl] == 1 || map[yd][xr] == 1)
		return (true);
	return (false);
}

void	_linear_movement(t_player *p, int orientation)
{
	double	new_y;
	double	new_x;
	double	teta;
	double	speed;
	float	pixel_speed = P_SPEED *  (float)cubed()->gmap->tile;
	
	if (p->w && (p->a || p->d))
	{
		speed = P_SPEED * 0.75;
		pixel_speed *= 0.75f;
	}
	else if (p->s && (p->a || p->d))
	{
		speed = P_SPEED * 0.75;
		pixel_speed *= 0.75f;
	}
	else
		speed = P_SPEED;
	teta = p->dir.teta;
	new_y = ((sin(teta) * speed) * orientation) + p->pos.y;
	new_x = ((cos(teta) * speed) * orientation) + p->pos.x;
	if (!_is_matrix_wall(new_y, p->pos.x))
	{
		p->pos.y = new_y;
		cubed()->gmap->player.y += (sin(teta) * pixel_speed) * orientation;
	}
	if (!_is_matrix_wall(p->pos.y, new_x))
	{
		p->pos.x = new_x;
		cubed()->gmap->player.x += (cos(teta) * pixel_speed) * orientation;
		
	}
}

void	_strafe_movement(t_player *p, int orientation)
{

	double	new_y;
	double	new_x;
	double	teta;
	double	speed;
	float	pixel_speed = P_SPEED * (float)cubed()->gmap->tile;

	if (p->w && (p->a || p->d))
	{
		speed = P_SPEED * 0.75;
		pixel_speed *= 0.75f;
	}
	else if (p->s && (p->a || p->d))
	{
		speed = P_SPEED * 0.75;
		pixel_speed *= 0.75f;
	}
	else
		speed = P_SPEED;
	teta = (3 * (PI / 2)) + p->dir.teta;
	new_y = (sin(teta) * speed * orientation) + p->pos.y;
	new_x = (cos(teta) * speed * orientation) + p->pos.x;
	if (!_is_matrix_wall(new_y, p->pos.x))
	{
		p->pos.y = new_y;
		cubed()->gmap->player.y += (sin(teta) * pixel_speed) * orientation;
	}
	if (!_is_matrix_wall(p->pos.y, new_x))
	{
		p->pos.x = new_x;
		cubed()->gmap->player.x += (cos(teta) * pixel_speed) * orientation;
		
	}
}
void	_spin(t_player *p, int wise)
{
	double	new_teta;
	t_pos	plane;

	new_teta = p->dir.teta + (wise * R_SPEED);
	if (new_teta >= 2 * PI)
		new_teta = 0;
	if (new_teta < 0)
		new_teta = 2 * PI;
	p->dir.teta = new_teta;
	p->dir.y = sin(p->dir.teta);
	p->dir.x = cos(p->dir.teta);
	plane = p->plane;
	p->plane.x = p->plane.x * cos(wise * R_SPEED) - p->plane.y * sin(wise * R_SPEED);
	p->plane.y = plane.x * sin(wise * R_SPEED) + p->plane.y * cos(wise * R_SPEED);
}

// void	_handle_walk(t_player *p)
// {
// 	if (p->w)
// 		_linear_movement(p, -1);
// 	if (p->s)
// 		_linear_movement(p, +1);
// 	if (p->a)
// 		_strafe_movement(p, -1);
// 	if (p->d)
// 		_strafe_movement(p, +1);
// }

// void	_handle_rotation(t_player *p)
// {
// 	if (p->r_a)
// 		_spin(p, -1);
// 	if (p->r_d)
// 		_spin(p, +1);
// 	if (p->r_w)
// 		return ;
// 	if (p->r_s)
// 		return ;
// }

// void	_handle_input(t_player *p)
// {
// 	_handle_walk(p);
// 	_handle_rotation(p);
// }