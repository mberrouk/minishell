/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:22:17 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 11:27:01 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

void	sort_export(t_env *env, int indice, int size)
{
	char	*max;
	t_env	*copy;

	copy = env;
	while (copy)
	{
		copy->index = 0;
		copy = copy->next;
	}
	size = env_len(env);
	while (indice <= size)
	{
		copy = env;
		max = come_max(env);
		while (1)
		{
			if (ft_strcmp(max, copy->key) == 0)
			{
				copy->index = indice;
				indice++;
				break ;
			}
			copy = copy->next;
		}
	}
}

void	print(t_env *env, t_env *tmp, int size)
{
	size = env_len(env);
	while (size > 0)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->index == size)
			{
				if (tmp->val)
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
				else 
					printf("declare -x %s\n", tmp->key);
				size--;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	help(t_env *tmp, char *key, char *value, int x)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && x)
		{
			tmp->val = ft_strjoin(tmp->val, value);
			break ;
		}
		if (!ft_strcmp(tmp->key, key))
		{
			if (!value)
				break ;
			free(tmp->val);
			tmp->val = value;
			break ;
		}
		tmp = tmp->next;
	}
}

t_env	*env_new(char *s1, char *s2)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = s1;
	new->index = 0;
	new->val = s2;
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		t = *lst;
		while (t->next)
			t = t->next;
		t->next = new;
	}
}
