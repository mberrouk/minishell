#include "../include/shell.h"

static int	count_digit(int num)
{
	int	d;

	d = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		d++;
	}
	return (d);
}

static void	convert_ita(char *num, int n)
{
	int	y;

	y = count_digit(n) - 1;
	num[y + 1] = '\0';
	while (y > -1)
	{
		num[y] = (n % 10) + 48;
		n /= 10;
		y--;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		i;

	i = 0;
	len = count_digit(n) + 1;
	if (n < 0)
	{
		if (n == (-2147483648))
			return (num = ft_strdup("-2147483648"));
		n *= -1;
		len++;
	}
	num = (char *)malloc(sizeof(char) * len);
	if (!num)
		return (NULL);
	if (count_digit(n) < (len - 1))
	{
		num[i] = '-';
		i++;
	}
	convert_ita(&num[i], n);
	return (num);
}