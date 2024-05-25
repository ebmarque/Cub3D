/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:50:09 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 16:32:43 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *buffer, int target)
{
	int	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i])
	{
		if ((unsigned char)buffer[i] == (unsigned char)target)
			return (&buffer[i]);
		i++;
	}
	if ((unsigned char )buffer[i] == (unsigned char)target)
		return (&buffer[i]);
	return (NULL);
}
