/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:04:15 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 01:13:44 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr(int fd, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(fd, str[i]);
		i++;
	}
}

void	ft_putnbr(int fd, int num)
{
	if (num >= 10)
		ft_putnbr(fd, num / 10);
	write(fd, &"0123456789"[num % 10], 1);
}

void	_chois(int fd, char format, va_list *va)
{
	if (format == 'c')
		ft_putchar(fd, (int)va_arg(*va, int));
	else if (format == 's')
		ft_putstr(fd, (char *)va_arg(*va, char *));
	else if (format == 'd')
		ft_putnbr(fd, (int)va_arg(*va, int));
}

void	_print(int fd, char *str, ...)
{
	va_list	va;

	va_start(va, str);
	while (*str)
	{
		if (*(str) == '%')
		{
			if (*(str + 1))
				str++;
			else
				return ;
			_chois(fd, *str, &va);
		}
		else
			ft_putchar(fd, *str);
		str++;
	}
	va_end(va);
}
