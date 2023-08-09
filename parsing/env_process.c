/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:07:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 00:07:10 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

t_env	*new_node(char *key, char *val, int idx)
{
	t_env	*new;

	(void)idx;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0x00);
	new->next = 0x00;
	new->key = key;
	new->val = val;
	return (new);
}

void	add_node(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	check_pwd(t_env **envlist, int i)
{
	t_env	*tmp;

	tmp = *envlist;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			if (tmp->val)
				free(tmp->val);
			tmp->val = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_node(envlist, new_node(ft_strdup("OLDPWD"), NULL, i));
}

void	fetch_env(t_env **envlist, char **env)
{
	int		i;
	char	**arg;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		arg = ft_split(env[i], '=');
		if (arg)
			add_node(envlist, new_node(ft_strdup(arg[0])\
			, ft_strdup(arg[1]), i));
		free_double(arg);
		i++;
	}
	check_pwd(envlist, i);
}

int	getenv_size(void)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = g_info.g_env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
