/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 19:57:47 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	double_len(char **ptr)
{
	int	len;

	len = 0;
	if (!ptr || !*ptr)
		return (0);
	while (ptr[len])
		len++;
	return (len);
}

void	copy_str(char *new, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
}

char	**_dptr_copy(char **new, char **old, char *laststr)
{
	int	i;

	i = 0;
	while (old && old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = ft_strdup(laststr);
	free_double(old);
	if (laststr)
		free(laststr);
	new[i + 1] = NULL;
	return (new);
}

char	**join_double(char **fir, char *last)
{
	char	**new;
	int		len;

	len = double_len(fir) + 1;
	if (!len)
		return (0x00);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
	{
		free_double(fir);
		perror("Error");
		exit(1);
	}
	return (_dptr_copy(new, fir, last));
}
