/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_in_doublq.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:58:18 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 15:53:29 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	not_expand(char **value, char *arg)
{
	int	len;

	len = len_to_spchar(arg);
	*value = ft_strjoin(*value, ft_substr(arg, 0, len));
	return (len);
}

int	expand_it(char **value, char *arg, char **env)
{
	int	len;

	len = len_to_spchar(arg);
	*value = ft_strjoin(*value, get_var(ft_substr(arg, 0, len), env));
	return (len);
}

int	handl_cases(char **value, char *arg, int ndol)
{
	int		i;
	int		len;

	(void)ndol;
	i = 0;
	if (arg[i] == '?')
		*value = ft_strjoin(*value, ft_itoa(g_info.exit_status));
	if (sp_remove(arg[i]) && (arg[i] != '\'' && arg[i] != '\"') \
	&& arg[i] != '$')
		i++;
	else
	{
		if ((arg[i] == '\"' || arg[i] == '\''))
			*value = ft_realloc(*value, arg[i - 1]);
		len = len_to_spchar(arg);
		*value = ft_strjoin(*value, ft_substr(arg, i, len));
		i += len;
	}
	return (i);
}

char	*expan_in_dquots(char *arg, char **env)
{
	int		i;
	char	*value;
	int		ndol;

	i = 0;
	value = NULL;
	while (arg[i])
	{
		while (arg[i] != '$' && arg[i])
			value = ft_realloc(value, arg[i++]);
		ndol = skip_dollar(&value, &arg[i]);
		i += ndol;
		if ((ndol && ndol % 2 == 0)
			|| (i && arg[i - 1] == '$' && check_sp_char(arg[i])))
		{
			if (ndol && ndol % 2 == 0)
				i += not_expand(&value, &arg[i]);
			else
				i += handl_cases(&value, &arg[i], ndol);
			continue ;
		}
		i += expand_it(&value, &arg[i], env);
	}
	free(arg);
	return (value);
}
