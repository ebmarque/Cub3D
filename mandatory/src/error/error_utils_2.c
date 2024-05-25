/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:13:00 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 15:19:19 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static	int	_recover_block_2(char c)
{
	if (c == 'h')
		return (5);
	else if (c == 'i')
		return (6);
	else if (c == 'j')
		return (7);
	else if (c == 'k')
		return (8);
	else if (c == 'l')
		return (9);
	return ((int)c);
}

int	_recover_block(char c)
{
	if (c == 'n')
		return ('N');
	else if (c == 's')
		return ('S');
	else if (c == 'e')
		return ('E');
	else if (c == 'w')
		return ('W');
	else if (c == 'o')
		return ('O');
	else if (c == 'c')
		return ('C');
	else if (c == 'a')
		return (0);
	else if (c == 's')
		return (1);
	else if (c == 'd')
		return (2);
	else if (c == 'f')
		return (3);
	else if (c == 'g')
		return (4);
	return (_recover_block_2(c));
}

static void	_fill_block2(t_file *t, t_point current, int c)
{
	if (c == 5)
		t->map[current.y][current.x] = 'h';
	else if (c == 6)
		t->map[current.y][current.x] = 'j';
	else if (c == 7)
		t->map[current.y][current.x] = 'k';
	else if (c == 8)
		t->map[current.y][current.x] = 'l';
	else
		t->map[current.y][current.x] = 'z';
}

void	_fill_block(t_file *t, t_point current, int c)
{
	if (c == 'N')
		t->map[current.y][current.x] = 'n';
	else if (c == 'S')
		t->map[current.y][current.x] = 's';
	else if (c == 'E')
		t->map[current.y][current.x] = 'e';
	else if (c == 'W')
		t->map[current.y][current.x] = 'w';
	else if (c == 'O')
		t->map[current.y][current.x] = 'o';
	else if (c == 'C')
		t->map[current.y][current.x] = 'c';
	else if (c == 0)
		t->map[current.y][current.x] = 'a';
	else if (c == 1)
		t->map[current.y][current.x] = 's';
	else if (c == 2)
		t->map[current.y][current.x] = 'd';
	else if (c == 3)
		t->map[current.y][current.x] = 'f';
	else if (c == 4)
		t->map[current.y][current.x] = 'g';
	else
		_fill_block2(t, current, c);
}

bool	_is_player_on_edge(t_file *t)
{
	if ((int)t->p_position.x == 0 || (int)t->p_position.x == t->map_width)
		return (true);
	if ((int)t->p_position.y == 0 || (int)t->p_position.y == t->map_end_line)
		return (true);
	return (false);
}
