/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:05:24 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/14 22:12:23 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_is_matrix_wall(float ny, float nx)
{
	int	**map;
	int	y;
	int	x;

	y = (int)(ny);
	x = (int)(nx);
	map = cubed()->content->map;
	if (map[y][x] == 1)
		return (true);
	return (false);
}

void	_linear_movement(t_player *p, int orientation)
{
	double	new_y;
	double	new_x;
	double	teta;
	double	speed;

	if (p->w && (p->a || p->d))
		speed = P_SPEED * 0.75;
	else if (p->s && (p->a || p->d))
		speed = P_SPEED * 0.75;
	else
		speed = P_SPEED;
	teta = p->dir.teta;
	new_y = ((sin(teta) * speed) * orientation) + p->pos.y;
	new_x = ((cos(teta) * speed) * orientation) + p->pos.x;
	// if (!_is_matrix_wall(new_y, p->pos.x))
		p->pos.y = new_y;
	// if (!_is_matrix_wall(p->pos.y, new_x))
		p->pos.x = new_x;
}

void	_strafe_movement(t_player *p, int orientation)
{

	double	new_y;
	double	new_x;
	double	teta;
	double	speed;
	if (p->w && (p->a || p->d))
		speed = P_SPEED * 0.75;
	else if (p->s && (p->a || p->d))
		speed = P_SPEED * 0.75;
	else
		speed = P_SPEED;
	teta = (3 * (PI / 2)) + p->dir.teta;
	new_y = (sin(teta) * speed * orientation) + p->pos.y;
	new_x = (cos(teta) * speed * orientation) + p->pos.x;
	// if (!_is_matrix_wall(new_y, p->pos.x))
		p->pos.y = new_y;
	// if (!_is_matrix_wall(p->pos.y, new_x))
		p->pos.x = new_x;
	/* if (new_y >= 0 && new_y + P_SIZE <= HEIGHT)
		p->pos.y = new_y;
	if (new_x >= 0 && new_x + P_SIZE<= WIDTH)
		p->pos.x = new_x; */
}
void	_spin(t_player *p, int wise)
{
	double	new_teta;

	new_teta = p->dir.teta + (wise * R_SPEED);
	if (new_teta >= 2 * PI)
		new_teta = 0;
	if (new_teta < 0)
		new_teta = 2 * PI;
	p->dir.teta = new_teta;
	p->dir.y = sin(p->dir.teta);
	p->dir.x = cos(p->dir.teta);
}

void	_handle_walk(t_player *p)
{
	if (p->w)
		_linear_movement(p, -1);
	if (p->s)
		_linear_movement(p, +1);
	if (p->a)
		_strafe_movement(p, -1);
	if (p->d)
		_strafe_movement(p, +1);
}

void	_handle_rotation(t_player *p)
{
	if (p->r_a)
		_spin(p, -1);
	if (p->r_d)
		_spin(p, +1);
	if (p->r_w)
		return ;
	if (p->r_s)
		return ;
}

void	_handle_input(t_player *p)
{
	_handle_walk(p);
	_handle_rotation(p);
}