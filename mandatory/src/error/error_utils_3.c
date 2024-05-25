/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:53:15 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 15:59:18 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

bool	_is_valid_map_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'O' \
		&& c != 'C' && c != '0' && c != '1' && c != '2' && c != '3' \
		&& c != '4' && c != '5' && c != '6' && c != '7' && c != '8' \
		&& c != '9' && !ft_is_space(c))
		return (false);
	return (true);
}

/**
 * Checks if a given line is a valid map line.
 *
 * @param line The line to be checked.
 * @return 1 if the line is valid, 0 otherwise.
 */
int	_is_valid_map_line(char *line)
{
	int	i;

	i = -1;
	if (!line || !*line)
		return (1);
	while (line[++i])
	{
		if (!_is_valid_map_char(line[i]))
		{
			printf("IN LINE: %s\n", line);
			printf("Caracter: %c --> is not valid\n", line[i]);
			return (0);
		}
	}
	return (1);
}

/**
 * Checks if the characters in the map file are valid.
 * 
 * @param file The path to the map file.
 * @param start The line number to start checking from.
 * @param fd The file descriptor of the map file.
 * @param content The structure containing information about the file content.
 */
void	_check_valid_map_char(char *file, int start, int fd, t_file *content)
{
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line && --start > 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!_is_valid_map_line(line))
		{
			free(line);
			_read_all_file(fd);
			_clean_content(content);
			_exit_error(INVALID_MAP_LINE);
		}
		free(line);
		line = get_next_line(fd);
		start++;
	}
	free(line);
	close(fd);
}

void	_update_map_width(t_file *content, char *line)
{
	int		size;
	char	*nl;

	nl = ft_strtrim(line, "\n");
	size = ft_strlen(nl);
	if (size > content->map_width)
		content->map_width = size;
	free(nl);
}
