/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:54:02 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 04:27:36 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

int	get_key(t_env *temp, char *str);
int	err_msg_inden(char *av, char *par);

int	chhe(char *av, char *par)
{
	int	i;

	i = 0;
	if (check_sp_char(av[i]))
		return (err_msg_inden(av, par));
	while (av[i])
	{
		if (sp_at_end(av[i]) && av[i] != '=' && av[i] != '+')
			return (err_msg_inden(av, par));
		i++;
	}
	return (1);
}

int	export_help(char **av, t_env *env, char *value, int i)
{
	char	*key;
	int		x;

	key = cat_equals(av[i], &x, 0);
	if (!key || (key && chhe(key, "export") == 1))
	{
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
