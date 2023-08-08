/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:22:43 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 03:28:52 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"

int	env_len(t_env *env)
{
	int	len;

    len = 0;
    while (env)
	{
		len++;
		env = (env)->next;
	}
    return (len);
}

char	*come_max(t_env *env)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->index == 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strcmp(max, env->key) < 0)
		{
			if (env->index == 0)
				max = env->key;
		}
		env = env->next;
	}
	return (max);
}

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
				if (tmp->val && ft_strcmp(tmp->key, "_"))
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
				else if (ft_strcmp(tmp->key, "_"))
					printf("declare -x %s%c\n", tmp->key, '\0');
				size--;
				break ;
			}
			tmp = tmp->next;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////


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

int	len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	export_add(char *key, char *value)
{
	t_env	*new;

	new = env_new(key, value);
	envadd_back(&g_info.g_env, new);
}

char	*cat_equals(char *str, int *x, int i)
{
	int		len;
	char	*p;

	(*x) = 0;
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	p = malloc(len + 2);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
		if (str[i] == '=' || str[i] == '+')
		{
			p[i] = '\0';
			if (str[i] == '+')
				(*x) = 1;
			return (p);
		}
	}
	if (p)
		free(p);
	return (NULL);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
} 

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
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
		else if (!str[i] || str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))  /** added !str[i]**/
			break ;
		else
		{
			error = 1;
			break ;
		}
	}
	if (error == 1)
	{
		//ft_error("minishell: export: '", str, "': not a valid identifier", 1);
		//printf("\n error --> %s\n", str);
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
		{
			
			help(env, ft_strdup(key), value, x);
		}
		else
		{
			export_add(ft_strdup(key), value);
		}
		free(key);
		return (1);
	}
	return (0);
}

void	export_(char **av, t_env *env)
{
	int i;
	
	i = 1;
	while (av[i])
	{
		if (!export_help(av, env, NULL, i))
			break ;
		i++;
	}	
}

void    ft_export(char **av, t_env *env)
{
	int	size;
	int j;
	int i = 1;

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
        		_print(2,"minishell: export: '%s' not a valid identifier\n", av[i]);
        		g_info.exit_status = 1;
        		break;
    		}
        	j = 0;
        	while(av[i][j])
        	{
            	if (av[i][j] == ' ')
            	{
                	_print(2,"minishell: export: '%s' not a valid identifier\n", av[i]);
                	g_info.exit_status = 1;
                	break;
            	}
      	      	j++;
       		}
        	i++;
   		}
		export_(av, env);
	}
}
