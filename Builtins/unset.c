/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:24:30 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 04:05:47 by mberrouk         ###   ########.fr       */
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
	else if (chhe(av, "unset") == -1)
		return ;
	check(env_list, av);
	g_info.exit_status = 0;
}
