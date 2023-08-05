
#include "./include/shell.h"

void ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

void ft_putstr(int fd, va_list va)
{
	char *str;

	str = va_arg(va, char *);
	while (*str)
	{
		ft_putchar(fd, *str);
		str++;
	}
}

void	ft_putnbr(int fd, int num)
{
	if (num >= 10)
		ft_putnbr(fd, num / 10);
	write(fd, &"0123456789"[num % 10], 1);
}

void	_chois(int fd, char format, va_list va)
{
	if (format == 'c')
		ft_putchar(fd, (int)va_arg(va, int));
	else if (format == 's')
		ft_putstr(fd, va);
	else if (format == 'd')
		ft_putnbr(fd, (int)va_arg(va, int));
}

void _print(int fd, char *str, ...)
{
	va_list va;

	va_start(va, str);
	while (*str)
	{
		if (*(str) == '%')
		{
			if (*(str + 1))
				str++;
			else
				return ;
			_chois(fd, *str, va);
		}
		else
			ft_putchar(fd, *str);
		str++;
	}
	va_end(va);
}
