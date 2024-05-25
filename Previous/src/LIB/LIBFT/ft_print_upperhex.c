/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_upperhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:30:01 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:44 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_putnbr(long long int nbr, char *base, int *i)
{
	long long int	nb;

	nb = nbr;
	if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		*i = *i + 1;
		nb *= -1;
	}
	if (nb >= 16)
		ft_recursive_putnbr((nb / 16), base, i);
	nb = nb % 16;
	*i = *i + 1;
	ft_putchar_fd(base[nb], 1);
}

int	ft_print_upperhex(t_print *tab)
{
	long long int	nb;
	int				i;

	i = 0;
	nb = va_arg(tab->args, int);
	if (nb < 0)
		nb = 4294967296 + nb;
	ft_recursive_putnbr(nb, "0123456789ABCDEF", &i);
	return (i);
}
