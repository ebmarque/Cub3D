/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:19 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/23 18:46:34 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

// void	_open_door(t_point p, t_file *t)
// {
// 	if (t->map[p.y - 1][p.x] == 1)
// 		t->map[p.y - 1][p.x] = 2;
// 	if (t->map[p.y + 1][p.x] == 1)
// 		t->map[p.y + 1][p.x] = 2;
// 	if (t->map[p.y][p.x - 1] == 1)
// 		t->map[p.y][p.x - 1] = 2;
// 	if (t->map[p.y][p.x + 1] == 1)
// 		t->map[p.y][p.x + 1] = 2;
// 	t->map[p.y][p.x] = 'O';
// }

// void	_close_door(t_point p, t_file *t)
// {
// 	if (t->map[p.y - 1][p.x] == 2)
// 		t->map[p.y - 1][p.x] = 1;
// 	if (t->map[p.y + 1][p.x] == 2)
// 		t->map[p.y + 1][p.x] = 1;
// 	if (t->map[p.y][p.x - 1] == 2)
// 		t->map[p.y][p.x - 1] = 1;
// 	if (t->map[p.y][p.x + 1] == 2)
// 		t->map[p.y][p.x + 1] = 1;
// 	t->map[p.y][p.x] = 'C';
// }

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
	if (k == E)
		_look_for_door(cubed()->player, cubed()->content);
	if (k == ENTER)
		p->map_view *= -1;
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
