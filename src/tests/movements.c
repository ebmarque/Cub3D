/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:02:09 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:05:55 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


void	_walk_up(t_p *game)
{
	if (game->center.y - 3 < HEIGHT && (game->center.y - 3) > 0)
		game->center.y -= 3;

}

void	_walk_down(t_p *game)
{
	if (game->center.y +3 < HEIGHT && (game->center.y + 3) > 0)
		game->center.y += 3;

}

void	_walk_left(t_p *game)
{
	if (game->center.x - 3 < WIDTH && (game->center.x - 3) > 0)
		game->center.x -= 3;
}

void	_walk_right(t_p *game)
{
	if (game->center.x + 3 < WIDTH && (game->center.x + 3) > 0)
		game->center.x += 3;
}
