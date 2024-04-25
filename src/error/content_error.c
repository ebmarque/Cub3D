/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:34:03 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/25 18:06:24 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	_check_color_values(t_rgb color)
{
	if (color.r < 0 || color.b < 0 || color.g < 0)
		return (-1);
	if (color.r > 255 || color.b > 255 || color.g > 255)
		return (-1);
	return (0);
}

int	_set_floor(char **split, t_file *content)
{
	char	**color_values;

	if (content->floor.is_set)
		return (-1);
	color_values = ft_split(split[1], ",");
	if (_get_split_size(color_values) != 3)
	{
		ft_free_split(color_values);
		return(-1);
	}
	content->floor.r = ft_atol(color_values[0]);
	content->floor.b = ft_atol(color_values[1]);
	content->floor.g = ft_atol(color_values[2]);
	content->floor.is_set = true;
	if (_check_color_values(content->floor) == -1)
	{
		ft_free_split(color_values);
		return(-1);
	}
	ft_free_split(color_values);
	return(0);
}

int	_set_ceiling(char **split, t_file *content)
{
	char	**color_values;

	if (content->ceiling.is_set)
		return (-1);
	color_values = ft_split(split[1], ",");
	if (_get_split_size(color_values) != 3)
	{
		ft_free_split(color_values);
		return(-1);
	}
	content->ceiling.r = ft_atol(color_values[0]);
	content->ceiling.b = ft_atol(color_values[1]);
	content->ceiling.g = ft_atol(color_values[2]);
	content->ceiling.is_set = true;
	if (_check_color_values(content->ceiling) == -1)
	{
		ft_free_split(color_values);
		return(-1);
	}
	ft_free_split(color_values);
	return(0);
}

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

int	_check_file_line(char *line, t_file *content)
{
	char	**split;

	if (!line || !*line || !ft_strncmp(line, "\n", 2))
		return (0);
	split	= ft_split(line, " ");
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

void	_elements_validation(char *file, t_file *content)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
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
}



t_file	*_check_map_content(char *file)
{
	t_file	*content;

	content	= (t_file *)malloc(sizeof(t_file));
	if (!content)
		_exit_error(MEMORY_ERROR);
	ft_bzero(content, sizeof(t_file));
	_elements_validation(file, content);
	_print_content_variable(content);
	_clean_content(content);
	return (content);
}