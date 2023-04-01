/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:11:09 by robegarc          #+#    #+#             */
/*   Updated: 2023/01/30 15:39:21 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i += write(1, &s[i], 1);
	return (i);
}

int	ft_output(va_list v, const char ptr)
{
	int	out;

	out = 0;
	if (ptr == 'c')
		out += ft_putchar(va_arg(v, int));
	else if (ptr == 's')
		out += ft_putstr(va_arg(v, char *));
	else if (ptr == 'd' || ptr == 'i')
		out += print_int(va_arg(v, int));
	else if (ptr == '%')
		out += ft_putchar('%');
	else if (ptr == 'p')
	{
		out += ft_putstr("0x");
		out += print_p(va_arg(v, intptr_t));
	}
	else if (ptr == 'u')
		out += print_uint(va_arg(v, unsigned int));
	else if (ptr == 'x' || ptr == 'X')
		out += print_hex(va_arg(v, unsigned int), ptr);
	return (out);
}

int	ft_printf(char const *ptr, ...)
{
	int		i;
	int		out;
	va_list	v;

	i = 0;
	out = 0;
	va_start(v, ptr);
	while (ptr[i])
	{
		if (ptr[i] == '%')
		{
			out += ft_output(v, ptr[i + 1]);
			i++;
		}
		else
			out += ft_putchar(ptr[i]);
		i++;
	}
	va_end(v);
	return (out);
}
