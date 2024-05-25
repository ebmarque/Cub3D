/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:30:45 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/23 17:32:33 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

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
	int	i;
	int	j;

	i = 0;
	while (i < t->matrix_dimensions.y)
	{
		j = 0;
		while (j < t->matrix_dimensions.x)
		{
			if (t->map[i][j] == 0)
				printf(BG_WHITE"  "RESET);
			else if (t->map[i][j] == 'x')
				printf(INVISIBLE"  "RESET);
			else if (_is_player_char(t->map[i][j]))
				printf(BG_GREEN"  "RESET);
			else if (t->map[i][j] == 3)
				printf(GREEN"x"RESET);
			else
				printf(BG_RED"  "RESET);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n");
}
