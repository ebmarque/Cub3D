/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:29 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/23 19:42:23 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_check_file_name(char *file)
{
	char	*name;

	if (!file || !*file)
	{
		ft_putstr_fd(RED"ERROR: Invalid map name."RESET, 2);
		exit(EXIT_FAILURE);
	}
	name = file + (ft_strlen(file) - 4);
	if (ft_strncmp(name, ".cub", 5))
	{
		ft_putstr_fd(RED"ERROR: Map file with wrong extension" \
			" < .cub > ."RESET, 2);
		exit(EXIT_FAILURE);
	}
}

void	_check_file_permissions(char *file)
{
	int	fd;

	fd = open(file, F_OK);
	if (fd == -1)
	{
		ft_putstr_fd(RED"ERROR: File cannot be accessed."RESET, 2);
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(file, X_OK);
	if (fd == -1)
	{
		ft_putstr_fd(RED"ERROR: File" \
			"(Permission for execution denided)."RESET, 2);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	_check_empty_file(char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_WRONLY);
	line = get_next_line(fd);
	if (!line || !*line)
	{
		ft_putstr_fd(RED"ERROR: Empty map file."RESET, 2);
		exit(EXIT_FAILURE);
	}
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
	{
		ft_putstr_fd(RED"ERROR: Wrong number of arguments."RESET, 2);
		exit(EXIT_FAILURE);
	}
	_check_file_name(argv[1]);
	_check_file_permissions(argv[1]);
	_check_empty_file(argv[1]);
}
