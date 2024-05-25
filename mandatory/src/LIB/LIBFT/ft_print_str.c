/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:29:58 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:41 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(t_print *tab)
{
	char	*str;
	int		len;

	str = va_arg(tab->args, char *);
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (len);
}
