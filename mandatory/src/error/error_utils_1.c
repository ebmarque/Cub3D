/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:08:31 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 15:16:51 by ebmarque         ###   ########.fr       */
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
	content->floor.g = ft_atol(color_values[1]);
	content->floor.b = ft_atol(color_values[2]);
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
	content->ceiling.g = ft_atol(color_values[1]);
	content->ceiling.b = ft_atol(color_values[2]);
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

bool	_duplicate_player(t_file *t)
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
