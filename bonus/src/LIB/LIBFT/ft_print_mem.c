/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:29:50 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:34 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_putnbr(unsigned long long nbr, char *base, int *i)
{
	unsigned long long	nb;

	nb = nbr;
	if (nb >= 16)
		ft_recursive_putnbr((nb / 16), base, i);
	nb = nb % 16;
	*i = *i + 1;
	ft_putchar_fd(base[nb], 1);
}

int	ft_print_mem(t_print *tab)
{
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = va_arg(tab->args, unsigned long long);
	if (nb == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_recursive_putnbr(nb, "0123456789abcdef", &i);
	i = i + 2;
	return (i);
}
