/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/23 16:23:09 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Frees the memory allocated for the content of a file structure.
 * @param content The file structure whose content needs to be cleaned.
 */
void	_clean_content(t_file *content)
{
	if (content->no_t != NULL)
		free(content->no_t);
	if (content->so_t != NULL)
		free(content->so_t);
	if (content->we_t != NULL)
		free(content->we_t);
	if (content->ea_t != NULL)
		free(content->ea_t);
	if (content->map)
		_free_map(content);
	if (content)
		free(content);
}

/**
 * Reads all the lines from a file descriptor and frees the memory allocated
 * for each line.
 * @param fd The file descriptor to read from.
 */
void	_read_all_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

/**
 * Checks if all the required elements in the file structure are set.
 * @param t The file structure to check.
 * @return 1 if all elements are set, 0 otherwise.
 */
int	_all_elements_set(t_file *t)
{
	if (!t->ceiling.is_set || !t->floor.is_set \
		|| !t->no_t || !t->so_t || !t->we_t || !t->ea_t)
		return (0);
	return (1);
}

/**
 * Prints the content variables of a file structure.
 * @param t The file structure to print.
 */
void	_print_content_variable(t_file *t)
{
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", t->no_t, t->so_t, \
		t->we_t, t->ea_t);
	printf("FLOOR SET: %ld, %ld, %ld\nCEILING SET: %ld, %ld, %ld\n", \
		t->floor.r, t->floor.g, t->floor.b, t->ceiling.r, \
		t->ceiling.g, t->ceiling.b);
}

/**
 * Extracts a texture from a line.
 * @param line The line containing the texture.
 * @return The extracted texture.
 */
char	*_give_texture(char *line)
{
	if (!ft_strchr(line, '\n'))
		return (ft_strdup(line));
	return (ft_strndup(line, ft_strlen(line) - 1));
}
