/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:40:19 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/20 19:44:43 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **array, int position, bool full)
{
	int	i;

	i = 0;
	if (!full)
	{
		while (i < position)
		{
			free(array[i]);
			i++;
		}
		free(array[i]);
		free(array);
		return ;
	}
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}
