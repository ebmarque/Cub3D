/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:19 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/03 13:05:13 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	_key_pressed(int k, t_player *p)
{
	if (k == W)
		p->w = true;
	else if (k == S)
		p->s = true;
	else if (k == A)
		p->a = true;
	else if (k == D)
		p->d = true;
	else if (k == UP)
		p->r_w = true;
	else if (k == DOWN)
		p->r_s = true;
	else if (k == LEFT)
		p->r_a = true;
	else if (k == RIGHT)
		p->r_d = true;
	else
		return (-1);
	return (0);
}

int	_key_release(int k, t_player *p)
{
	if (k == W)
		p->w = false;
	else if (k == S)
		p->s = false;
	else if (k == A)
		p->a = false;
	else if (k == D)
		p->d = false;
	else if (k == UP)
		p->r_w = false;
	else if (k == DOWN)
		p->r_s = false;
	else if (k == LEFT)
		p->r_a = false;
	else if (k == RIGHT)
		p->r_d = false;
	else
		return (-1);
	return (0);
}
int	_raycasting_loop(void *data)
{
	t_cub	*cd;

	cd = (t_cub *)data;
	_handle_input(cd->player);
}