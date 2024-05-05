/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:29 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/05 20:41:21 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Checks if the file name is valid and has the correct extension.
 * 
 * @param file The file name to be checked.
 */
static void	_check_file_name(char *file)
{
	char	*name;

	if (!file || !*file)
		_exit_error(INVALID_NAME);
	name = file + (ft_strlen(file) - 4);
	if (ft_strncmp(name, ".cub", 5))
		_exit_error(WRONG_EXT);
}

/**
 * Checks the file permissions of the given file.
 * If the file does not exist or cannot be accessed, it exits with an error.
 * If the file does not have execute permissions, it exits with an error.
 *
 * @param file The path to the file to check permissions for.
 */
static void	_check_file_permissions(char *file)
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

/**
 * Checks if a file is empty by reading its contents line by line.
 * If the file is empty, it exits the program with an error message.
 *
 * @param file The path to the file to be checked.
 */
static void	_check_empty_file(char *file)
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

/**
 * Initializes and returns a player struct with the initial 
 * orientation based on the map.
 * 
 * @param t The file struct containing the map.
 * @return A pointer to the initialized player struct.
 */
static t_player *_player_initial_orientation(t_file *t)
{
	t_player	*p;
	int			**map;
	char		ori;

	p = ft_calloc(1, sizeof(t_player));
	p->pos.x = t->p_position.x;
	p->pos.y = t->p_position.y;
	map = t->map;
	ori = (char)map[(int)t->p_position.y][(int)t->p_position.x];
	if (ori == 'N')
		p->dir.teta = PI / 2;
	else if (ori == 'S')
		p->dir.teta = 3 * (PI / 2);
	else if (ori == 'W')
		p->dir.teta = PI;
	else if (ori == 'E')
		p->dir.teta = 0;
	p->dir.x = cos(p->dir.teta);
	p->dir.y = sin(p->dir.teta);
	return (p);
}

/**
 * Checks for errors in the command line arguments and the input file.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 */
void	_check_errors(int argc, char **argv)
{
	if (argc != 2)
		_exit_error(INVALID_ARGC);
	_check_file_name(argv[1]);
	_check_file_permissions(argv[1]);
	_check_empty_file(argv[1]);
	cubed()->content = _check_map_content(argv[1]);
	cubed()->player = _player_initial_orientation(cubed()->content);
}
