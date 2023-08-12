/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:33:08 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 23:49:36 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	is_charest(char c, char *charest)
{
	int	j;

	j = 0;
	while (charest[j] != '\0')
	{
		if (charest[j] == c)
			return (1);
		j++;
	}
	if (c == '\0')
	{
		return (1);
	}
	return (0);
}

int	size_strs(char *str, char *sep)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (is_charest(str[i], sep) == 0 && is_charest(str[i + 1], sep) == 1)
			size++;
		i++;
	}
	return (size);
}

void	strs_cp(char *strs, char *str, char *sep )
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_charest(str[i], sep) == 0)
		{
			strs[i] = str[i];
			i++;
		}
		else
			return ;
		strs[i] = '\0';
	}
}

void	allo_strs(char **strs, char *str, char *sep)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_charest(str[i], sep) == 1)
			i++;
		else
		{
			j = 0;
			while (is_charest(str[j + i], sep) == 0)
				j++;
			strs[count] = (char *)malloc(sizeof(char) * (j + 1));
			strs_cp(strs[count], (str + i), sep);
			i += j;
			count++;
		}
	}
}

char	**ultra_split(char *str, char *charset)
{
	char	**strs;
	int		size;

	if (!str)
		return (NULL);
	size = size_strs(str, charset);
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (0);
	strs[size] = 0;
	allo_strs(strs, str, charset);
	return (strs);
}
