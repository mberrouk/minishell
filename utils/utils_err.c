/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:34:04 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 01:20:40 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	**free_double(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
	return (NULL);
}

void	*print_err(char *str)
{
	write(STDERR_FILENO, "Error: ", 7);
	if (str && *str)
		write(STDERR_FILENO, str, ft_strlen(str));
	return (NULL);
}
