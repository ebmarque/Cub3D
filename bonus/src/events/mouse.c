/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:08:55 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/28 21:43:59 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	_mouse_click(int button, int x, int y, void *data)
{
	(void)data;
	if (button == 1)
	{
		cubed()->mouse.on = 1;
		cubed()->mouse.pos.x = x;
		cubed()->mouse.pos.y = y;
		cubed()->mouse.prev = cubed()->mouse.pos;
	}
	if (button == 3)
		cubed()->mouse.on = 0;
	return (0);
}

static void	_motion_spin(int x)
{
	double		new_teta;
	t_pos		plane;
	t_player	*p;

	p = cubed()->player;
	new_teta = cubed()->player->pos.teta + (x * MOUSE_SPEED);
	if (new_teta >= 2 * PI)
		new_teta = 0;
	if (new_teta < 0)
		new_teta = 2 * PI;
	cubed()->player->pos.teta = new_teta;
	p->dir.x = cos(p->pos.teta);
	p->dir.y = sin(p->pos.teta);
	plane.x = p->plane.x;
	p->plane.x = p->plane.x * cos(x * MOUSE_SPEED) \
		- p->plane.y * sin(x * MOUSE_SPEED);
	p->plane.y = plane.x * sin(x * MOUSE_SPEED) \
		+ p->plane.y * cos(x * MOUSE_SPEED);
}

int	_mouse_move(int x, int y, void *data)
{
	(void)data;
	if ((x == cubed()->mouse.prev.x && y == cubed()->mouse.prev.y) \
		|| !cubed()->mouse.on)
		return (0);
	if (cubed()->mouse.on)
	{
		_motion_spin(cubed()->mouse.prev.x - x);
		mlx_mouse_move(cubed()->mx_var->mlx, cubed()->mx_var->win, \
			cubed()->mouse.prev.x, cubed()->mouse.prev.y);
	}
	return (0);
}
