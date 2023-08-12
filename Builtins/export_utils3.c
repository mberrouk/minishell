/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:55:38 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 20:37:26 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

void	export_(char **av, t_env *env)
{
	int	i;

	i = 1;
	while (av[i])
	{
		export_help(av, env, NULL, i);
		i++;
	}
}

void	ft_export(char **av, t_env *env)
{
	int	size;

	size = 0;
	if (av[1] == NULL)
	{
		sort_export(env, 1, size);
		print(env, NULL, 0);
	}
	else
		export_(av, env);
}
