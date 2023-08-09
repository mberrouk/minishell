/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:55:38 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 04:04:02 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	err_msg_inden(char *av, char *par)
{
	_print(2, "minishell: %s: '%s' not a valid identifier\n", par, av);
	g_info.exit_status = 1;
	return (-1);
}

int	chhe(char **av, char *par)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (av[i])
	{
		if (check_sp_char(*av[i]))
			return (err_msg_inden(av[i], par));
		j = 0;
		while (av[i][j] && av[i][j] != '=')
		{
			if (sp_at_end(av[i][j]))
				return (err_msg_inden(av[i], par));
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
		if (chhe(av, "export") == 0)
			export_(av, env);
	}
}
