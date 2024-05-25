/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque < ebmarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:33 by ebmarque          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:53 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_tab(t_print *tab)
{
	tab->dash = 0;
	tab->dot = 0;
	tab->hstg = 0;
	tab->plus = 0;
	tab->space = 0;
	tab->zero = 0;
	tab->tlen = 0;
	tab->error = 0;
}

int	ft_is_flag(char c)
{
	if (c == '-' || c == '+' || c == '#'
		|| c == ' ' || c == '.' || c == '0')
	{
		return (1);
	}
	return (0);
}

int	ft_check_specifier(t_print *tab, const char *format, int i)
{
	if (format[i] == 'c')
		return (ft_print_char(tab));
	else if (format[i] == 's')
		return (ft_print_str(tab));
	else if (format[i] == 'p')
		return (ft_print_mem(tab));
	else if (format[i] == 'd' || format[i] == 'i')
		return (ft_print_int(tab));
	else if (format[i] == 'u')
		return (ft_print_usgdec(tab));
	else if (format[i] == 'x')
		return (ft_print_lowhex(tab));
	else if (format[i] == 'X')
		return (ft_print_upperhex(tab));
	else if (format[i] == '%')
		return (ft_print_percent());
	return (0);
}

int	ft_action_sign(t_print *tab, const char *format, int i)
{
	while (ft_is_flag(format[i]))
	{
		if (format[i] == '+')
			tab->plus = 1;
		if (format[i] == '#')
			tab->hstg = 1;
		if (format[i] == ' ')
			tab->space = 1;
		if (format[i] == '.')
			tab->dot = 1;
		if (format[i] == '0')
			tab->zero = 1;
		if (format[i] == '-')
			tab->dash = 1;
		i++;
	}
	tab->tlen = ft_check_specifier(tab, format, i);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	t_print	*tab;
	int		i;
	int		len;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	ft_init_tab(tab);
	va_start(tab->args, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			i = ft_action_sign(tab, format, i + 1);
		else
			len = len + write(1, &format[i], 1);
		i++;
		len = len + tab->tlen;
		ft_init_tab(tab);
	}
	va_end(tab->args);
	free(tab);
	return (len);
}
