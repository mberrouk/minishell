/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:07 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 01:59:50 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/shell.h"

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
