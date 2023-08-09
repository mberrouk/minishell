/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:22 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 01:25:12 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	is_sep(char s, char sp)
{
	if (sp == s)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}

static char	**count_dup(char **s, char *str, char c)
{
	int	i;
	int	j;
	int	w;

	w = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (is_sep(str[j + i], c) != 1)
				j++;
			s[w] = (char *)malloc(sizeof(char) * j + 1);
			if (!s[w])
				return (free_double(s));
			ft_strlcpy(s[w], &str[i], j + 1);
			i += j;
			w++;
		}
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**word;
	int		size;
	int		i;

	i = 0;
	word = NULL;
	size = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (is_sep(s[i], c) == 0 && is_sep(s[i + 1], c) == 1)
			size++;
		i++;
	}
	word = (char **)malloc(sizeof(char *) * (size + 1));
	if (!word)
		return (NULL);
	word[size] = 0;
	return (count_dup(word, (char *)s, c));
}
