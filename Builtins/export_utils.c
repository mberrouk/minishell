/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:53:31 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 21:29:38 by hoakoumi         ###   ########.fr       */
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

int	err_msg_inden(char *av, char *par)
{
	_print(2, "minishell: %s: '%s' not a valid identifier\n", par, av);
	g_info.exit_status = 1;
	return (-1);
}

int	chhe(char *av, char *par)
{
	int	i;

	i = 0;
	printf("%s\n", av);
	if (check_sp_char(av[i]))
		return (err_msg_inden(av, par));
	while (av[i])
	{
		printf("%d\n", sp_at_end(av[i]));
		if (sp_at_end(av[i]))
				return (err_msg_inden(av, par));
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
		// printf("%d\n", chhe(key, "export"));
		if (key)
			value = ft_substr(av[i], len_equal(av[i]) + 1,
					ft_strlen(av[i]));
		else if (!key)
			key = ft_strdup(av[i]);
		if (get_key(env, key))
			help(env, ft_strdup(key), value, x);
		if (chhe(key, "export"))
			return(-1);
		else if (!get_key(env, key) )
			export_add(ft_strdup(key), value);
		free(key);
		return (1);
	}
	return (0);
}
