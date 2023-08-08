/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:01:21 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 17:45:37 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	check_option(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[i] == '-' && str[i + 1] != '\0' && str[i + 1] == 'n')
		{
			i++;
			while (str[i])
			{
				if (str[i] == 'n')
					i++;
				else
					return (-1);
			}
			return (0);
		}
		j++;
	}
	return (-1);
}

void	echo(char **av)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	j = 0;
	while (av[j])
	{
		if (av[i] != NULL && check_option(av[i]) == 0)
		{
			flag = 1;
			i++;
		}
		j++;
	}
	while (av[i])
	{
		if (av[i])
		{
			printf("%s", av[i]);
			i++;
			if (av[i] != NULL)
				printf(" ");
		}
	}
	if (!flag)
		printf("\n");
}

void	ft_echo(char **av)
{
	echo(av);
	g_info.exit_status = 0;
}
