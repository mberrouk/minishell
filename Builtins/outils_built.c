/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:15:37 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 03:37:50 by mberrouk         ###   ########.fr       */
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

size_t	ft_atoi(const	char	*str)
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
	if (vars.sig == 1 && vars.r >= __LONG_LONG_MAX__)
		return (__LONG_LONG_MAX__);
	if (vars.sig == -1 && vars.r >= __LONG_LONG_MAX__)
		return (__LONG_LONG_MAX__);
	return (vars.r * vars.sig);
}
