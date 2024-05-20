/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:15:27 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/19 20:20:04 by ebmarque         ###   ########.fr       */
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

static	int	_recover_block(char c)
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

static void	_fill_block(t_file *t, t_point current, int c)
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

static bool	_fill_validation(t_file *t, t_point size, t_point current)
{
	if (current.x < 0 || current.y < 0 || current.x > size.x - 1\
		|| current.y > size.y - 1)
		return (false);
	if (((current.x == 0 || current.y == 0 || current.x == size.x - 1
		|| current.y == size.y - 1) && t->map[current.y][current.x] == 0)
		|| t->map[current.y][current.x] == 'x')
	{
		_print_map(t);
		_clean_content(t);
		_exit_error(OPEN_WALLS);
	}
	if (!_is_player_char(t->map[current.y][current.x]) \
		&& t->map[current.y][current.x] != 0)
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
	t_point c;

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
			if (t->map[c.y][c.x] == 0)
				_fill(t, size, c, t->map[t->begin.y][t->begin.x]);
		}
	}
}

bool	_is_player_on_edge(t_file *t)
{
	if ((int)t->p_position.x == 0 || (int)t->p_position.x == t->map_width)
		return (true);
	if ((int)t->p_position.y == 0 || (int)t->p_position.y == t->map_end_line)
		return (true);
	return (false);
}
static bool	_duplicate_player(t_file *t)
{
	int	i;
	int	j;
	int	player_counter;

	i = -1;
	player_counter = 0;
	while (++i < t->matrix_dimensions.y)
	{
		j = -1;
		while (++j < t->matrix_dimensions.x)
		{
			if (_is_player_char(t->map[i][j]))
				player_counter++;
		}
	}
	if (player_counter > 1)
		return (true);
	return (false);
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