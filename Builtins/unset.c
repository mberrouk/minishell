/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:24:30 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 02:55:55 by hoakoumi         ###   ########.fr       */
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

int	err_msg_inden(char *av, char *par);

int	special_char_check(char *av, char *par)
{
	int	i;

	i = 0;
	if (check_sp_char(av[i]))
		return (err_msg_inden(av, par));
	while (av[i])
	{
		if (sp_at_end(av[i]))
			return (err_msg_inden(av, par));
		i++;
	}	
	return (1);
}

void	check(t_env **env_list, char **av)
{
	t_unset	vars;

	vars.i = 1;
	vars.prev = NULL;
	vars.current = *env_list;
	while (av[vars.i])
	{
		if (special_char_check(av[vars.i], "unset") == 1)
			find_and_remove(env_list, av[vars.i], vars);
		vars.i++;
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
	check(env_list, av);
	g_info.exit_status = 0;
}
