/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:19 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 20:03:19 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_look_for_door(t_player *p, t_file *t)
{
	t_point	interaction;

	interaction.y = (int)((sin(p->pos.teta) * -0.9f) + p->pos.y);
	interaction.x = (int)((cos(p->pos.teta) * 0.9f) + p->pos.x);
	if (t->map[(int)interaction.y][(int)interaction.x] == 'C')
		t->map[interaction.y][interaction.x] = 'O';
	else if (t->map[(int)interaction.y][(int)interaction.x] == 'O')
		t->map[interaction.y][interaction.x] = 'C';
}

int	_key_pressed(int k, void *data)
{
	t_player	*p;

	p = (t_player *)data;
	if (k == ESC)
		_terminate_cubed();
	if (k == W)
		p->w = 1;
	if (k == S)
		p->s = 1;
	if (k == A)
		p->a = 1;
	if (k == D)
		p->d = 1;
	if (k == LEFT)
		p->r_a = 1;
	if (k == RIGHT)
		p->r_d = 1;
	else
		return (-1);
	return (0);
}

int	_key_release(int k, void *data)
{
	t_player	*p;

	p = (t_player *)data;
	if (k == ESC)
		_terminate_cubed();
	if (k == W)
		p->w = 0;
	if (k == S)
		p->s = 0;
	if (k == A)
		p->a = 0;
	if (k == D)
		p->d = 0;
	if (k == LEFT)
		p->r_a = 0;
	if (k == RIGHT)
		p->r_d = 0;
	else
		return (-1);
	return (0);
}

int	_raycasting_loop(void)
{
	t_player	*p;

	p = cubed()->player;
	if (p->w)
		_linear_movement(p, -1);
	if (p->s)
		_linear_movement(p, +1);
	if (p->a)
		_strafe_movement(p, -1);
	if (p->d)
		_strafe_movement(p, +1);
	if (p->r_a)
		_spin(p, +1);
	if (p->r_d)
		_spin(p, -1);
	return (0);
}
