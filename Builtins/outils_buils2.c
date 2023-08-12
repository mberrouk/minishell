/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_buils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:29:44 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 02:30:39 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

t_env	*searching_key(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(key, env_list->key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	set_oldpwd(t_env **envlist, char *dir)
{
	t_env	*tmp;

	tmp = *envlist;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->val);
			tmp->val = fstrdup(dir);
			return ;
		}
		tmp = tmp->next;
	}
	envadd_back(envlist, env_new(ft_strdup("OLDPWD"), ft_strdup(dir)));
}

void	set_pwd(t_env **envlist, char *dir)
{
	t_env	*tmp;

	tmp = *envlist;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->val);
			tmp->val = fstrdup(dir);
			return ;
		}
		tmp = tmp->next;
	}
	envadd_back(envlist, env_new(ft_strdup("PWD"), ft_strdup(dir)));
}
