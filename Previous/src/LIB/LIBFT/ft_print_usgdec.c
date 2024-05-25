/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_usgdec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:30:04 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:47 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(long long int n)
{
	int	digits;

	digits = 1;
	if (n < 0)
	{
		digits++;
		n = -n;
	}
	while (n / 10 > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static void	ft_fill_result(long long int n, char *result, int digits)
{
	int	check;

	check = 0;
	result[digits] = '\0';
	while (digits > check)
	{
		if (n < 0)
		{
			result[0] = '-';
			n = -n;
			check++;
		}
		else
		{
			result[digits - 1] = n % 10 + '0';
			n = n / 10;
			digits--;
		}
	}
}

static char	*ft_itoa_u(long long int n)
{
	char	*result;
	int		digits;

	digits = ft_count_digits(n);
	result = (char *)malloc(sizeof(char) * (digits + 1));
	if (result == NULL)
		return (NULL);
	ft_fill_result(n, result, digits);
	return (result);
}

int	ft_print_usgdec(t_print *tab)
{
	long long int		nb;
	char				*number;
	int					len;

	nb = va_arg(tab->args, int);
	if (nb < 0)
		nb = 4294967296 + nb;
	number = ft_itoa_u(nb);
	len = ft_strlen(number);
	ft_putstr_fd(number, 1);
	free(number);
	return (len);
}
