/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:36 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/25 17:27:09 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	_ignore_spaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_is_space(line[i]))
			i++;
		else
			return(i);
	}
	return (i);
}

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

int	_is_map_line(char **split)
{
	if (!split)
		return (2);
	if (!_is_element(split[0]) && _get_split_size(split) > 1)
		return (1);
	return (0);
}

void	_exit_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
