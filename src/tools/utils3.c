/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:08:07 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/26 13:08:42 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Checks the permissions of a file.
 * 
 * @param file The path of the file to check.
 * @return 1 if the file does not exist,
 * 2 if the file is not executable,
 * 0 otherwise.
 */
int	_check_t_file_permissions(char *file)
{
	int	fd;

	fd = open(file, F_OK);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(file, X_OK);
	if (fd == -1)
		return (2);
	close(fd);
	return (0);
}

/**
 * Checks if a file is empty.
 * 
 * @param file The path of the file to check.
 * @return 1 if the file is empty, 0 otherwise.
 */
int	_check_t_empty_file(char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line || !*line)
		return (1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
