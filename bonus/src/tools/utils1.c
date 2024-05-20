/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:36 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/27 19:31:31 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Calculates the size of a string array.
 *
 * @param line The string array.
 * @return The size of the string array.
 */
int	_get_split_size(char **line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		i++;
	return (i);
}

/**
 * Checks if a given line is an element identifier.
 *
 * @param line The line to check.
 * @return 1 if the line is an element identifier, 0 otherwise.
 *         Returns 2 if the line is NULL.
 */
int	_is_element(char *line)
{
	if (!line)
		return (2);
	if (!ft_strncmp(line, "NO", 3) || !ft_strncmp(line, "SO", 3) \
		|| !ft_strncmp(line, "WE", 3) || !ft_strncmp(line, "EA", 3) \
		|| !ft_strncmp(line, "F", 2) || !ft_strncmp(line, "C", 2))
		return (1);
	return (0);
}

/**
 * Checks if a given line in the map is valid.
 * 
 * @param split - The array of strings representing the line split by spaces.
 * @return 0 if the line is a valid map line, 1 if it is not a valid map line
 * but has more than one element, 2 if the split array is NULL.
 */
int	_is_map_line(char *line)
{
	char	**split;

	if (!line || !*line || !ft_strncmp(line, "\n", 2))
		return (0);
	split = ft_split(line, EMPTY_SPACES);
	if (!split[0] || !*split[0] || !ft_strncmp(split[0], "\n", 2))
	{
		ft_free_split(split);		
		return (0);
	}
	if (!_is_element(split[0]))
	{
		ft_free_split(split);
		return (1);
	}
	ft_free_split(split);
	return (0);
}

/**
 * Exits the program with an error message.
 * 
 * @param msg The error message to display.
 */
void	_exit_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
