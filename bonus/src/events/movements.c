/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:05:24 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/25 19:44:11 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_wall_char(int c)
{
	if ((c >= 1 && c <= 9) || c == 'C')
		return (true);
	return (false);
}

bool	_is_matrix_wall(float ny, float nx)
{
	int	**map;
	int	yu;
	int	xl;
	int	yd;
	int	xr;

	yu = (int)(ny);
	yd = (int)(ny + 0.5f);
	xl = (int)(nx);
	xr = (int)(nx + 0.5f);
	map = cubed()->content->map;
	if (_wall_char(map[yu][xl]) \
		|| _wall_char(map[yu][xr]) \
		|| _wall_char(map[yd][xl]) \
		|| _wall_char(map[yd][xr]))
		return (true);
	return (false);
}

void	_linear_movement(t_player *p, int orientation)
{
	double	new_y;
	double	new_x;
	double	teta;
	double	speed;
	float	pixel_speed;

	if ((p->w && (p->a || p->d)) || (p->s && (p->a || p->d)))
		speed = P_SPEED * 0.75;
	else
		speed = P_SPEED;
	pixel_speed = speed * (float)cubed()->gmap->tile;
	teta = p->pos.teta;
	new_y = ((sin(teta) * speed) * orientation) + p->pos.y;
	new_x = ((-1) * (cos(teta) * speed) * orientation) + p->pos.x;
	if (!_is_matrix_wall(new_y, p->pos.x))
	{
		p->pos.y = new_y;
		cubed()->gmap->player.y += (sin(teta) * pixel_speed) * orientation;
	}
	if (!_is_matrix_wall(p->pos.y, new_x))
	{
		p->pos.x = new_x;
		cubed()->gmap->player.x += ((-1) * (cos(teta) * pixel_speed)) \
			* orientation;
	}
}

void	_strafe_movement(t_player *p, int orientation)
{
	double	new_y;
	double	new_x;
	double	teta;
	double	speed;
	float	pixel_speed;

	if ((p->w && (p->a || p->d)) || (p->s && (p->a || p->d)))
		speed = P_SPEED * 0.75;
	else
		speed = P_SPEED;
	pixel_speed = speed * (float)cubed()->gmap->tile;
	teta = p->pos.teta;
	new_y = ((cos(teta) * speed) * orientation) + p->pos.y;
	new_x = ((sin(teta) * speed) * orientation) + p->pos.x;
	if (!_is_matrix_wall(new_y, p->pos.x))
	{
		p->pos.y = new_y;
		cubed()->gmap->player.y += (cos(teta) * pixel_speed) * orientation;
	}
	if (!_is_matrix_wall(p->pos.y, new_x))
	{
		p->pos.x = new_x;
		cubed()->gmap->player.x += (sin(teta) * pixel_speed) * orientation;
	}
}

void	_spin(t_player *p, int wise)
{
	double	new_teta;
	t_pos	plane;

	new_teta = p->pos.teta + (wise * R_SPEED);
	if (new_teta >= 2 * PI)
		new_teta = 0;
	if (new_teta < 0)
		new_teta = 2 * PI;
	p->pos.teta = new_teta;
	p->dir.x = cos(p->pos.teta);
	p->dir.y = sin(p->pos.teta);
	plane.x = p->plane.x;
	p->plane.x = p->plane.x * cos(wise * R_SPEED) \
		- p->plane.y * sin(wise * R_SPEED);
	p->plane.y = plane.x * sin(wise * R_SPEED) \
		+ p->plane.y * cos(wise * R_SPEED);
}
