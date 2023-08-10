/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:53:31 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 03:24:16 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	err_msg_inden(char *av, char *par);

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
		return (err_msg_inden(str, "export"));
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
