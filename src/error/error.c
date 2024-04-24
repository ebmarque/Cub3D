/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:29 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/24 18:22:31 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_check_file_name(char *file)
{
	char	*name;

	if (!file || !*file)
		_exit_error(INVALID_NAME);
	name = file + (ft_strlen(file) - 4);
	if (ft_strncmp(name, ".cub", 5))
		_exit_error(WRONG_EXT);
}

void	_check_file_permissions(char *file)
{
	int	fd;

	fd = open(file, F_OK);
	if (fd == -1)
		_exit_error(NO_ACCESS);
	close(fd);
	fd = open(file, X_OK);
	if (fd == -1)
		_exit_error(NO_RIGHTS);
	close(fd);
}

void	_check_empty_file(char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line || !*line)
		_exit_error(EMPTY_MAP);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	_check_erros(int argc, char **argv)
{
	if (argc != 2)
		_exit_error(INVALID_ARGC);
	_check_file_name(argv[1]);
	_check_file_permissions(argv[1]);
	_check_empty_file(argv[1]);
	// _check_map_content(argv[1]);
}
