/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:50:26 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/22 13:02:01 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	i = ft_strlen(s1);
	j = 0;
	join = (char *)malloc(sizeof(s1[0]) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[j])
	{
		join[j] = s1[j];
		j++;
	}
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	free(s1);
	join[i + j] = '\0';
	return (join);
}
