/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:15:27 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 20:09:18 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static bool	_fill_validation(t_file *t, t_point size, t_point current)
{
	if (current.x < 0 || current.y < 0 || current.x > size.x - 1 \
		|| current.y > size.y - 1)
		return (false);
	if (((current.x == 0 || current.y == 0 || current.x == size.x - 1 \
		|| current.y == size.y - 1) && (t->map[current.y][current.x] == 0 \
		|| t->map[current.y][current.x] == 'C' \
		|| t->map[current.y][current.x] == 'O')) \
		|| t->map[current.y][current.x] == 'x')
	{
		_print_map(t);
		_clean_content(t);
		_exit_error(OPEN_WALLS);
	}
	if (!_is_player_char(t->map[current.y][current.x]) \
		&& t->map[current.y][current.x] != 0 \
		&& t->map[current.y][current.x] != 'O')
		return (false);
	_fill_block(t, current, t->map[current.y][current.x]);
	return (true);
}

void	_fill(t_file *t, t_point size, t_point current, int p)
{
	if (!_fill_validation(t, size, current))
		return ;
	_fill(t, size, (t_point){current.x - 1, current.y}, p);
	_fill(t, size, (t_point){current.x + 1, current.y}, p);
	_fill(t, size, (t_point){current.x, current.y - 1}, p);
	_fill(t, size, (t_point){current.x, current.y + 1}, p);
}

void	_flood_fill(t_file *t)
{
	t_point	size;
	t_point	c;

	size.x = t->matrix_dimensions.x;
	size.y = t->matrix_dimensions.y;
	t->begin.x = (int)t->p_position.x;
	t->begin.y = (int)t->p_position.y;
	c.y = -1;
	while (++c.y < size.y)
	{
		c.x = -1;
		while (++c.x < size.x)
		{
			if (t->map[c.y][c.x] == 0 || t->map[c.y][c.x] == 'C' \
				|| t->map[c.y][c.x] == 'O' || _is_player_char(t->map[c.y][c.x]))
				_fill(t, size, c, t->map[t->begin.y][t->begin.x]);
		}
	}
}

void	_recover_matrix(t_file *t)
{
	int	i;
	int	j;

	i = -1;
	while (++i < t->matrix_dimensions.y)
	{
		j = -1;
		while (++j < t->matrix_dimensions.x)
			t->map[i][j] = _recover_block(t->map[i][j]);
	}
}

void	_check_map_rules(t_file *t)
{
	t->matrix_dimensions.y = t->map_end_line - t->map_start_line + 1;
	t->matrix_dimensions.x = t->map_width;
	if (t->matrix_dimensions.y <= 2 || t->matrix_dimensions.x < 3)
	{
		_clean_content(t);
		_exit_error(SMALL_MAP);
	}
	if (_is_player_on_edge(t) || _duplicate_player(t))
	{
		_clean_content(t);
		if (_is_player_on_edge(t))
			_exit_error(PLAYER_ON_EDGE);
		_exit_error(DUPLICATED_PLAYER);
	}
	_flood_fill(t);
	_recover_matrix(t);
	_print_map(t);
}
