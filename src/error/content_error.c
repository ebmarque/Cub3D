/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:34:03 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/24 20:53:14 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	_set_floor(char **split, t_file *content)
{
	
}

int	_save_element_data(char **split, t_file *content)
{
	int	size;

	size = _get_split_size(split);
	if (!ft_strncmp(split[0], "NO", 3) && size == 2 && !content->no_t)
		content->no_t = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "SO", 3) && size == 2 && !content->no_t)
		content->so_t = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "WE", 3) && size == 2 && !content->no_t)
		content->we_t = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "EA", 3) && size == 2 && !content->no_t)
		content->ea_t = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "F", 2) && size == 2)
		return (_set_floor(split, content));
	else if (!ft_strncmp(split[0], "C", 2) && size == 2)
		return (_set_ceiling(split, content));
	else
		return (-1);
	return (0);
}

void	_elements_validation(char *file, t_file *content)
{
	char	*line;
	char	**split;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, " ");
		if (_is_element(split))
			if (_save_element_data(split, content) == -1)
			{
				ft_free_split(split, 0, true);
				_read_all_file(file, fd);
				_clean_content(content);
				free(line);
				_exit_error(PARSING_ERROR);
			}
		free(line);
		ft_free_split(split, 0, true);
		line = get_next_line(fd);
	}
	ft_free_split(split, 0, true);
	free(line);
	close(fd);
}



t_file	*_check_map_content(char *file)
{
	t_file	*content;

	content	= (t_file *)malloc(sizeof(t_file));
	if (!content)
		_exit_error(MEMORY_ERROR);
	ft_bzero(content, sizeof(t_file));
	_elements_validation(file, content);
}