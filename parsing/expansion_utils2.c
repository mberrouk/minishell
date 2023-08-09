/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:21:04 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 01:34:00 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	if (s2[i] == '=')
		return (0);
	return (1);
}

int	skip_dollar(char **value, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '$')
	{
		if (i && !((i + 1) % 2))
			*value = ft_strjoin(*value, ft_strdup("$$"));
		else if (!arg[i + 1] || sp_stay(arg[i + 1]))
			*value = ft_realloc(*value, '$');
		i++;
	}
	return (i);
}

int	check_after_skip(char **value, char *arg, char sep, int *i)
{
	if (sep == '$' && (arg[*i] == '\'' || arg[*i] == '\"'))
		return (1);
	if (arg[*i] && sp_stay(arg[*i]))
	{
		*value = ft_strjoin(*value, ft_substr(&arg[*i], 0, \
		len_at_char(&arg[*i], '$')));
		*i += len_at_char(&arg[*i], '$');
		return (1);
	}
	return (0);
}

int	check_sep(char arg, char sep)
{
	return (arg == sep || !arg || (sep == '$' && (arg == '\'' || arg == '\"')));
}

char	*quots_expan(char **env, char *arg, char sep, int *i)
{
	char	*value;

	value = NULL;
	if (sep == '\"')
		value = expan_in_dquots(ft_substr(arg, 0, (*i) + 1), env);
	else if (sep == '\'')
		value = ft_substr(arg, 0, (*i) + 1);
	if (arg[*i])
		*i += 1;
	return (value);
}
