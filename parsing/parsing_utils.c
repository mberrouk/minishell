/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:56:26 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/05 06:42:54 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	len_to_spchar(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && !sp_at_end(arg[len]))
		len++;
	return (len);
}

int	skip_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	return (i);
}

int	len_at_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*get_var(char *var, char **env)
{
	int		j;
	int		len;
	char	*value;

    j = 0;
	len = ft_strlen(var);
	value = NULL;
	while (env[j])
	{
		if (!_strncmp(var, env[j], len))
			value = ft_strdup(&env[j][len + 1]);
		j++;
	}
	free(var);
	return (value);
}
