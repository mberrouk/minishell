/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:54:30 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/05 06:43:20 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*expan_arg(char *arg, char *env[])
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	value = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"' || arg[i] == '$')
			break ;
		if (arg[i] && check_sp_char(arg[i]))
			i += handl_spchar_cases(&arg[i], &value);
		else
		{
			len = len_to_spchar(&arg[i]);
			value = ft_strjoin(value, get_var(ft_substr(&arg[i], 0, len), env));
			i += len;
		}
		while (arg[i] != '$' && arg[i] != '\'' && arg[i] != '\"' && arg[i])
		{
			value = ft_realloc(value, arg[i]); 
			i++;
		}
	}
	free(arg);
	return (value);
}

char	*check_expan(char **env, char *arg, int ndolar, int i)
{
	char	*value;

	if (ndolar % 2 != 0)
		value = expan_arg(ft_substr(arg, ndolar, i - 1), env);
	else
		value = ft_substr(arg, ndolar, i - ndolar);
	return (value);
}

char	*continue_pars(char **env, char *arg, int *index, char sep)
{
	int		ndolr;
	int		i;
	char	*value;

	value = NULL;
	ndolr = skip_dollar(&value, arg);
	i = ndolr;
	if (!arg[i] || check_after_skip(&value, arg, sep, &i))
	{
		*index += i;
		return (value);
	}
	while (arg[i++])
	{
		if (check_sep(arg[i], sep))
		{
			if (sep == '\"' || sep == '\'')
				value = ft_strjoin(value, quots_expan(env, arg, sep, &i));
			else
				value = ft_strjoin(value, check_expan(env, arg, ndolr, i));
			break ;
		}
	}
	*index += i;
	return (value);
}

char	*pars_arg_expan(char *arg, char **env)
{
	int		i;
	char	sep;
	char	*value;

	i = 0;
	value = NULL;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '$' || arg[i] == '\'')
		{
			sep = arg[i];
			value = ft_strjoin(value, continue_pars(env, &arg[i], &i, sep));
		}
		else
		{
			value = ft_realloc(value, arg[i]);
			i++;
		}
	}
	free(arg);
	return (value);
}
