/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:15:27 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/28 21:09:05 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_fill(t_file *t, t_point size, t_point current, int p)
{
	if (current.x < 0 || current.y < 0 || current.x > size.x - 1\
		|| current.y > size.y - 1)
		return ;
    if (t->map[current.y][current.x] != 0 && t->map[current.y][current.x] != p)
		return ;
	if ((current.x == 0 || current.y == 0 || current.x == size.x - 1
		|| current.y == size.y - 1) && t->map[current.y][current.x] == 0)
		t->open_map = true;
	
	t->map[current.y][current.x] = 3;
    _fill(t, size, (t_point){current.x - 1, current.y}, p);
    _fill(t, size, (t_point){current.x + 1, current.y}, p);
    _fill(t, size, (t_point){current.x, current.y - 1}, p);
    _fill(t, size, (t_point){current.x, current.y + 1}, p);
    // _fill(t, size, (t_point){current.x + 1, current.y + 1}, p);
    // _fill(t, size, (t_point){current.x - 1, current.y - 1}, p);
    // _fill(t, size, (t_point){current.x + 1, current.y - 1}, p);
    // _fill(t, size, (t_point){current.x - 1, current.y + 1}, p);
}

void	_flood_fill(t_file *t)
{
	t_point	size;

	size.x = t->matrix_dimensions.x;
	size.y = t->matrix_dimensions.y;
	t->begin.x = (int)t->p_position.x;
	t->begin.y = (int)t->p_position.y;
    _fill(t, size, t->begin, t->map[t->begin.y][t->begin.x]);
	printf("BEGINIG POSITION: %d, %d\n", t->begin.x, t->begin.y);
	printf("Dimensoes da Matrix: %d : %d\n", size.y, size.x);
	_print_map(t);
	if (t->open_map)
	{
		_clean_content(t);
		_exit_error(OPEN_WALLS);
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
bool	_diplicated_player(t_file *t)
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
			if (t->map[i][j] != 1 && t->map[i][j] != 0)
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
		{
			if (t->map[i][j] == 3)
				t->map[i][j] = 0;
		}
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
	if (_is_player_on_edge(t) || _diplicated_player(t))
	{
		_clean_content(t);
		if (_is_player_on_edge(t))
			_exit_error(PLAYER_ON_EDGE);
		_exit_error(DUPLICATED_PLAYER);
	}
	_flood_fill(t);
	_recover_matrix(t);
}