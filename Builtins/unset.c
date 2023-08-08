/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:24:30 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 18:19:37 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

void	find_and_remove(t_env **env_list, char *key, t_unset vars)
{
	vars.current = *env_list;
	while (vars.current)
	{
		if (strcmp(key, vars.current->key) == 0)
		{
			if (vars.prev)
			{
				vars.prev->next = vars.current->next;
				free_env(vars.current);
				vars.current = vars.prev->next;
			}
			else
			{
				*env_list = vars.current->next;
				vars.current = *env_list;
			}
		}
		else
		{
			vars.prev = vars.current;
			vars.current = vars.current->next;
		}
	}
}

void	check(t_env **env_list, char **av)
{
	t_unset	vars;

	vars.i = 1;
	vars.prev = NULL;
	vars.current = *env_list;
	while (vars.current)
	{
		while (av[vars.i])
		{
			find_and_remove(env_list, av[vars.i], vars);
			vars.i++;
		}
		vars.i = 1;
		vars.prev = vars.current;
		if (vars.current)
			vars.current = vars.current->next;
	}
}

void	ft_unset(t_env **env_list, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!av || !av[1])
	{
		g_info.exit_status = 0;
		return ;
	}
	else if (av[1][0] >= '0' && av[1][0] <= '9')
	{
		_print(2, "minishell: unset: '%s' not a valid identifier\n", av[1]);
		g_info.exit_status = 1;
		return ;
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
			{
				_print(2, "minishell: unset: '%s' not a valid\
				 identifier\n", av[i]);
				g_info.exit_status = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	check(env_list, av);
	g_info.exit_status = 0;
}
