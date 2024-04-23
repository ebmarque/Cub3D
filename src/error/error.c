/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:29 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/23 19:34:25 by ebmarque         ###   ########.fr       */
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
	if (open(file, F_OK) == -1)
	{
		ft_putstr_fd(RED"ERROR: File cannot be accessed."RESET, 2);
		exit(EXIT_FAILURE);
	}
	if (open(file, X_OK) == -1)
	{
		ft_putstr_fd(RED"ERROR: File" \
			"(Permission for execution denided)."RESET, 2);
		exit(EXIT_FAILURE);
	}
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
