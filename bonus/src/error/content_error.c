/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:34:03 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 15:10:20 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Checks the validity of a file line and saves the element data.
 * 
 * @param line The line to be checked.
 * @param content The file content structure.
 * @return 0 if the line is valid, -1 if an error occurred.
 */
int	_check_file_line(char *line, t_file *content)
{
	char	**split;

	if (!line || !*line || !ft_strncmp(line, "\n", 2) \
		|| _all_elements_set(content))
		return (0);
	split = ft_split(line, EMPTY_SPACES);
	if (!split || !split[0] || !*split[0] || !ft_strncmp(split[0], "\n", 2))
	{
		ft_free_split(split);
		return (0);
	}
	if (_save_element_data(split, content) == -1)
	{
		ft_free_split(split);
		return (-1);
	}
	ft_free_split(split);
	return (0);
}

/**
 * Checks the texture files in the given content structure.
 * If any of the texture files have no access or insufficient rights,
 * or if any of the texture files are empty, it cleans the content
 * structure and exits with the corresponding error code.
 *
 * @param content The content structure containing the texture file paths.
 */
void	_check_texture_files(t_file *content)
{
	if (_check_t_file_permissions(content->no_t) == 1
		|| _check_t_file_permissions(content->so_t) == 1
		|| _check_t_file_permissions(content->we_t) == 1
		|| _check_t_file_permissions(content->ea_t) == 1)
	{
		_clean_content(content);
		_exit_error(NO_TEXTURE_ACCESS);
	}
	if (_check_t_file_permissions(content->no_t) == 2
		|| _check_t_file_permissions(content->so_t) == 2
		|| _check_t_file_permissions(content->we_t) == 2
		|| _check_t_file_permissions(content->ea_t) == 2)
	{
		_clean_content(content);
		_exit_error(NO_TEXTURE_RIGHTS);
	}
	if (_check_t_empty_file(content->no_t)
		|| _check_t_empty_file(content->so_t)
		|| _check_t_empty_file(content->we_t)
		|| _check_t_empty_file(content->ea_t))
	{
		_clean_content(content);
		_exit_error(EMPTY_TEXTURE);
	}
}

/**
 * Validates the elements in the file by checking each line.
 * 
 * @param file The path to the file to be validated.
 * @param content A pointer to the structure that holds the file content.
 */
void	_elements_validation(char *file, t_file *content)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line && !_all_elements_set(content))
	{
		if (_check_file_line(line, content) == -1)
		{
			free(line);
			_read_all_file(fd);
			_clean_content(content);
			_exit_error(PARSING_ERROR);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	_read_all_file(fd);
	_check_texture_files(content);
}

/**
 * Check the content of the map file and return a pointer to a t_file struct.
 *
 * @param file The path to the map file.
 * @return A pointer to a t_file struct containing the map file content.
 */
t_file	*_check_map_content(char *file)
{
	t_file	*content;

	content = (t_file *)malloc(sizeof(t_file));
	if (!content)
		_exit_error(MEMORY_ERROR);
	ft_bzero(content, sizeof(t_file));
	_elements_validation(file, content);
	_check_and_parse_map(content, file);
	return (content);
}
