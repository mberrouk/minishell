/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:55:38 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 02:11:46 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	chhe(char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] >= '0' && av[i][0] <= '9')
		{
			_print(2, "minishell: export: '%s' not a valid identifier\n", av[i]);
			g_info.exit_status = 1;
			return (-1);
			break ;
		}
		j = 0;
		while (av[i][j] && av[i][j] != '=')
		{
			if (av[i][j] == ' ' && av[i][j] != '=')
			{
				_print(2, "minishell: export: '%s' not a\
					valid identifier\n", av[i]);
				g_info.exit_status = 1;
				return (-1);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	export_(char **av, t_env *env)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!export_help(av, env, NULL, i))
			break ;
		i++;
	}	
}

void	ft_export(char **av, t_env *env)
{
	int	size;
	int	i;

	i = 1;
	size = 0;
	if (av[1] == NULL)
	{
		sort_export(env, 1, size);
		print(env, NULL, 0);
	}
	else
	{
		if (chhe(av) == 0)
			export_(av, env);
	}
}
