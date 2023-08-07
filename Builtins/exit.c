/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:10:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/07 22:20:51 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include "../include/shell.h"

int check_valid_arg(char **str)
 {
    int i;
    int j;

    i = 1;
    j = 0;

    while (str[i][j])
	{
		if (str[i][j] == '-' || str[i][j] == '+')
			j++;
		if (!(str[i][j] >= '0' && str[i][j] <= '9'))
			return (-2);
        if (str[2] && (str[i][j] >= '0' && str[i][j] <= '9')) 
            return (-1);
		j++;
	}
    return 0;
}

void	ft_exit(char **av)
{
	int	c;

	if (av[1] == NULL)
	{
		printf("exit\n");
		exit(g_info.exit_status);
	}
    if(av[1] && check_valid_arg(av) == -1)
    {
		_print(2,"exit\nminishell: exit: too many arguments\n");
        g_info.exit_status = 1;
		return ;
    }
    if(av[1] && check_valid_arg(av) == -2)
    {
		_print(2,"exit\nminishell: exit: %s: numeric argument required\n", av[1]);
        exit (255);
    }
    c = ft_atoi(av[1]);
	if (c == 4)
	{ 
		_print(2,"exit\nminishell: exit: %s: numeric argument required\n", av[1]);
		exit(255);
	}
	write(2, "exit\n", 5);
	exit(c);
}
