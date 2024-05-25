/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:32:35 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 15:57:18 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static bool	_all_dimension_set(t_file *t)
{
	if (t->map_start_line && t->map_end_line && t->map_width)
		return (true);
	return (false);
}

/**
 * Finds the start line of the map in the given file.
 *
 * @param file The path of the file to read.
 * @param i The current line number.
 * @param fd The file descriptor.
 * @return The line number where the map starts.
 */
static void	_find_map_start_line(char *file, int i, int fd, t_file *content)
{
	char	*line;

	fd = open(file, O_RDONLY);
	line = _tab_into_spaces(get_next_line(fd));
	while (line && !_all_dimension_set(content))
	{
		if (_is_map_line(line) && !content->map_start_line)
			content->map_start_line = i;
		if (!ft_strncmp("\n", line, 2) && content->map_start_line != 0)
			break ;
		free(line);
		line = _tab_into_spaces(get_next_line(fd));
		i++;
	}
	content->map_end_line = i - 1;
	free(line);
	close(fd);
	_read_all_file(fd);
}

/**
 * Checks for empty lines in the map.
 * 
 * @param file The path to the file containing the map.
 * @param content The structure containing the file content.
 * @param i The current line index.
 * @param fd The file descriptor.
 */
static void	_check_map_empty_lines(char *file, t_file *content, int i, int fd)
{
	char	*line;
	bool	empty_line;

	empty_line = false;
	fd = open(file, O_RDONLY);
	line = _tab_into_spaces(get_next_line(fd));
	while (line && ++i < content->map_start_line)
	{
		free(line);
		line = _tab_into_spaces(get_next_line(fd));
	}
	while (line)
	{
		if (!ft_strncmp("\n", line, 2) && !empty_line)
			empty_line = true;
		if (ft_strlen(line) > 1 && ft_strncmp("\n", line, 2) && empty_line)
		{
			free(line);
			_read_all_file(fd);
			_clean_content(content);
			_exit_error(EMPTY_MAP_LINE);
		}
		free(line);
		line = _tab_into_spaces(get_next_line(fd));
	}
}

static void	_get_map_width(t_file *content, char *file, int fd)
{
	int		i;
	char	*line;

	i = 1;
	fd = open(file, O_RDONLY);
	line = _tab_into_spaces(get_next_line(fd));
	while (line && i++)
	{
		if (i >= content->map_start_line && i <= content->map_end_line)
			_update_map_width(content, line);
		free(line);
		line = _tab_into_spaces(get_next_line(fd));
	}
	free(line);
	close(fd);
}

/**
 * Checks and parses the map from the given file.
 *
 * @param content The pointer to the file content structure.
 * @param file The path of the file to be checked and parsed.
 */
void	_check_and_parse_map(t_file *content, char *file)
{
	_find_map_start_line(file, 1, 0, content);
	_get_map_width(content, file, 1);
	_check_valid_map_char(file, content->map_start_line, 0, content);
	_check_map_empty_lines(file, content, -1, 0);
	_get_map(content, file);
	_check_map_rules(content);
}
