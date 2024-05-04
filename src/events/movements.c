/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:05:24 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/03 15:58:05 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_handle_walk(t_player *p)
{
	if (p->w)
		_linear_movement(p, +1);
	if (p->s)
		_linear_movement(p, -1);
	if (p->a)
		_strafe_movement(p, -1);
	if (p->d)
		_strafe_movement(p, +1);
}

void	_handle_ratation(t_player *p)
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