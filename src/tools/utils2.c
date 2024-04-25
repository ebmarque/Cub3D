/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/25 17:57:06 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

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
	ft_free_split(content->map);
	if (content)
		free(content);
}

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

int	_all_elements_set(t_file *t)
{
	if (!t->ceiling.is_set || !t->floor.is_set \
		|| !t->no_t || !t->so_t || !t->we_t || !t->ea_t)
		return (0);
	return (1);
}

void	_print_content_variable(t_file *t)
{
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", t->no_t, t->so_t, t->we_t, t->ea_t);
	printf("FLOOR SET: %d\nCEILING SET: %d\n", t->floor.is_set, t->ceiling.is_set);
}

char	*_give_texture(char *line)
{
	if (!ft_strchr(line, '\n'))
		return (ft_strdup(line));
	return (ft_strndup(line, ft_strlen(line) - 1));
}