/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:18 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/24 19:18:47 by ebmarque         ###   ########.fr       */
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
	ft_free_split(content->map, 0, true);
}

void	_read_all_file(char *file, int fd)
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
