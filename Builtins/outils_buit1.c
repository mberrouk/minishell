/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_buit1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:12:09 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 17:56:10 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"

char	*fstrdup(char *src)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[j])
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_env(t_env	*current)
{
	free(current->key);
	free(current->val);
	free(current);
}
