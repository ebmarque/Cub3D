/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:17:33 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/29 15:24:18 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	_fill_map_line(t_file *t, int i, int width, char *line)
{
	int	j;
	int	line_size;

	j = -1;
	line_size = ft_strlen(line);
	while (++j < width)
	{
		if (j < line_size)
		{
			if (line[j] == '1')
				t->map[i][j] = 1;
			else if (_is_player_char(line[j]))
			{
				t->p_position.x = (double)j;
				t->p_position.y = (double)i;
				t->map[i][j] = (int)line[j];
				t->p_position.is_set = true;
			}
			else
				t->map[i][j] = 0;
		}
		else
			t->map[i][j] = 0;
	}
	free(line);
}

void	_fill_map(t_file *content, char *file, int i, int fd)
{
	char	*line;
	int		j;

	j = 0;
	fd = open(file, O_RDONLY);
	line = _tab_into_spaces(get_next_line(fd));
	while (line && ++i <= content->map_end_line)
	{
		if (i >= content->map_start_line && i <= content->map_end_line)
		{
			_fill_map_line(content, j, content->map_width, ft_strtrim(line, "\n"));
			j++;
		}
		free(line);
		line = _tab_into_spaces(get_next_line(fd));
	}
	if (line)
		free(line);
	_read_all_file(fd);
	close(fd);
	if (content->p_position.is_set == false)
	{
		_clean_content(content);
		_exit_error(NO_PLAYER);
	}
}

void	_get_map(t_file *content, char *file)
{
	int	i;
	int	matrix_hight;

	matrix_hight = content->map_end_line - content->map_start_line + 1;
	i = -1;
	content->map = (int **)malloc(sizeof(int *) * matrix_hight);
	if (!content->map)
	{
		_exit_error(MEMORY_ERROR);
		_clean_content(content);
	}
	while (++i < matrix_hight)
	{
		content->map[i] = (int *)malloc(sizeof(int) * (content->map_width));
		if (content->map[i] == NULL)
		{
			_exit_error(MEMORY_ERROR);
			_clean_content(content);
		}
	}
	_fill_map(content, file, 0, 0);
}
