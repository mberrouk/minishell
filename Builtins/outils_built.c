/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:15:37 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/05 08:35:55 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static	int	w_space(const	char	*str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

int	ft_atoi(const	char	*str)
{
	t_at	vars;

	vars.r = 0;
	vars.sig = 1;
	vars.i = w_space(str);
	if (str[vars.i] == '-' )
	{
		vars.sig = vars.sig * (-1);
		vars.i++;
	}
	else if (str[vars.i] == '+')
		vars.i++;
	while (str[vars.i] <= '9' && str[vars.i] >= '0')
	{
		vars.r = vars.r * 10 + (str[vars.i] - '0');
		vars.i++;
	}
	if (str[vars.i])
		return (-1);
	if (vars.sig == 1 && vars.r > __LONG_LONG_MAX__)
		return (-1);
	if (vars.sig == -1 && vars.r > __LONG_LONG_MAX__)
		return (0);
	return (vars.r * vars.sig);
}
