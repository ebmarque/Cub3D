/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:08:07 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/28 19:45:31 by ebmarque         ###   ########.fr       */
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

size_t	_count_tabs(const char *source)
{
	size_t num_tabs;
	size_t i;

	num_tabs = 0;
	i = 0;
	if (!source || !*source)
		return (0);
	while (source[i] != '\0')
	{
		if (source[i] == '\t')
			num_tabs++;
		i++;
	}
	return (num_tabs);
}

void	_fill_tabs(const char *source, char *new_string)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (source[i] != '\0')
	{
		if (source[i] == '\t')
		{
			new_string[j++] = ' ';
			new_string[j++] = ' ';
			new_string[j++] = ' ';
			new_string[j++] = ' ';
		}
		else
			new_string[j++] = source[i];
		i++;
	}
	new_string[j] = '\0';
	
}

char	*_tab_into_spaces(char *source)
{
	size_t	source_size;
	size_t	num_tabs;
	size_t	nl_size;
	char	*new_string;

	source_size = ft_strlen(source);
	num_tabs = _count_tabs(source);
	if (num_tabs == 0)
		return (source);
	nl_size = source_size + (num_tabs * 4) + 1;
	new_string = (char *)malloc(nl_size);
	if (new_string == NULL)
		return (NULL);
	_fill_tabs(source, new_string);
	free(source);
	return (new_string);
}

void	_print_map(t_file *t)
{
	for (int i = 0; i < t->matrix_dimensions.y; i++)
	{
		for (int j = 0; j < t->matrix_dimensions.x; j++)
		{
			printf("%d", t->map[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}