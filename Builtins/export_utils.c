/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:17:41 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 18:35:08 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"

int	check_identifier(char *str, int i)
{
	int	error;

	error = 0;
	if (ft_isalpha(str[i]) && str[i] != '_')
		error = 1;
	i++;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			i++;
		else if (!str[i] || str[i] == '='
			|| (str[i] == '+' && str[i + 1] == '='))
			break ;
		else
		{
			error = 1;
			break ;
		}
	}
	if (error == 1)
	{
		_print(2, "minishell: export: '%s' not a valid identifier\n", str[1]);
		g_info.exit_status = 1;
		return (0);
	}
	return (1);
}

int	get_key(t_env *temp, char *str)
{
	t_env	*env;

	env = temp;
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

int	export_help(char **av, t_env *env, char *value, int i)
{
	char	*key;
	int		x;

	if (check_identifier(av[i], 0))
	{
		key = cat_equals(av[i], &x, 0);
		if (key)
			value = ft_substr(av[i], len_equal(av[i]) + 1,
					ft_strlen(av[i]));
		else
			key = ft_strdup(av[i]);
		if (get_key(env, key))
			help(env, ft_strdup(key), value, x);
		else
			export_add(ft_strdup(key), value);
		free(key);
		return (1);
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
	int	j;
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
		while (av[i])
		{
			if (av[i][0] >= '0' && av[i][0] <= '9')
			{
				_print(2, "minishell: export: '%s' not a valid\
				 identifier\n", av[i]);
				g_info.exit_status = 1;
				break ;
			}
			j = 0;
			while (av[i][j])
			{
				if (av[i][j] == ' ')
				{
					_print(2, "minishell: export: '%s' not a\
					 valid identifier\n", av[i]);
					g_info.exit_status = 1;
					break ;
				}
				j++;
			}
			i++;
		}
		export_(av, env);
	}
}
