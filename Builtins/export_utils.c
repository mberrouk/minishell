/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:53:31 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 03:43:37 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	_export_errmsg(char *str)
{
	_print(2, "minishell: export: '%s' not a valid identifier\n", str[1]);
	g_info.exit_status = 1;
	return (0);
}

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
		return (_export_errmsg(str));
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

int	checkk(char *key)
{
	int	i;

	i = 1;
	if (key[i] >= 0 && key[i] <= '9')
		return (-1);
	i++;
	while (key[i])
	{
		if (key[i] == ' ')
			return (-1);
		i++;
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
