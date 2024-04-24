/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:36 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/24 18:21:08 by ebmarque         ###   ########.fr       */
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

int	_is_element(char **split)
{
	if (!split)
		return (2);
	if (!ft_strncmp(split[0], "NO", 3) || !ft_strncmp(split[0], "SO", 3) \
		|| !ft_strncmp(split[0], "WE", 3) || !ft_strncmp(split[0], "EA", 3) \
		|| !ft_strncmp(split[0], "F", 2) || !ft_strncmp(split[0], "C", 2))
		return (1);
	return (0);
}

int	_is_map_line(char **split)
{
	if (!split)
		return (2);
	if (_is_element(split) == 1 && _get_split_size(split) > 1)
		return (1);
	return (0);
}

void	_exit_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
