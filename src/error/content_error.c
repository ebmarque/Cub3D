/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:34:03 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 15:27:18 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Checks if the RGB color values are valid.
 * 
 * @param color The RGB color to check.
 * @return 0 if the color values are valid, -1 otherwise.
 */
int	_check_color_values(t_rgb color)
{
	if (color.r < 0 || color.b < 0 || color.g < 0)
		return (-1);
	if (color.r > 255 || color.b > 255 || color.g > 255)
		return (-1);
	return (0);
}

/**
 * Sets the floor color based on the given split values.
 * 
 * @param split The split values containing the RGB color values.
 * @param content The file content structure.
 * @return 0 if the floor color is successfully set, -1 otherwise.
 */
int	_set_floor(char **split, t_file *content)
{
	char	**color_values;

	if (content->floor.is_set)
		return (-1);
	color_values = ft_split(split[1], ",");
	if (_get_split_size(color_values) != 3)
	{
		ft_free_split(color_values);
		return (-1);
	}
	content->floor.r = ft_atol(color_values[0]);
	content->floor.b = ft_atol(color_values[1]);
	content->floor.g = ft_atol(color_values[2]);
	content->floor.is_set = true;
	if (_check_color_values(content->floor) == -1)
	{
		ft_free_split(color_values);
		return (-1);
	}
	ft_free_split(color_values);
	return (0);
}

/**
 * Sets the ceiling color based on the given split values.
 * 
 * @param split The split values containing the RGB color values.
 * @param content The file content structure.
 * @return 0 if the ceiling color is successfully set, -1 otherwise.
 */
int	_set_ceiling(char **split, t_file *content)
{
	char	**color_values;

	if (content->ceiling.is_set)
		return (-1);
	color_values = ft_split(split[1], ",");
	if (_get_split_size(color_values) != 3)
	{
		ft_free_split(color_values);
		return (-1);
	}
	content->ceiling.r = ft_atol(color_values[0]);
	content->ceiling.b = ft_atol(color_values[1]);
	content->ceiling.g = ft_atol(color_values[2]);
	content->ceiling.is_set = true;
	if (_check_color_values(content->ceiling) == -1)
	{
		ft_free_split(color_values);
		return (-1);
	}
	ft_free_split(color_values);
	return (0);
}

/**
 * Saves the data of an element based on the given split array.
 * 
 * @param split - The array containing the split elements.
 * @param content - The file content structure to store the data.
 * @return 0 if successful, -1 otherwise.
 */
int	_save_element_data(char **split, t_file *content)
{
	int	size;

	size = _get_split_size(split);
	if (!ft_strncmp(split[0], "NO", 3) && size == 2 && !content->no_t)
		content->no_t = _give_texture(split[1]);
	else if (!ft_strncmp(split[0], "SO", 3) && size == 2 && !content->so_t)
		content->so_t = _give_texture(split[1]);
	else if (!ft_strncmp(split[0], "WE", 3) && size == 2 && !content->we_t)
		content->we_t = _give_texture(split[1]);
	else if (!ft_strncmp(split[0], "EA", 3) && size == 2 && !content->ea_t)
		content->ea_t = _give_texture(split[1]);
	else if (!ft_strncmp(split[0], "F", 2) && size == 2)
		return (_set_floor(split, content));
	else if (!ft_strncmp(split[0], "C", 2) && size == 2)
		return (_set_ceiling(split, content));
	else
	{
		if (!_all_elements_set(content) || _is_element(split[0]))
			return (-1);
	}
	return (0);
}

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
	split = ft_split(line, " \t\r\v\f\a\b\n");
	if (!split[0] || !*split[0] || !ft_strncmp(split[0], "\n", 2))
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
	_read_all_file(fd);
	close(fd);
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
