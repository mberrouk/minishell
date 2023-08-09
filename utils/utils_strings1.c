/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:36:03 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 01:19:14 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	if ((char)c == '\0')
		return (&((char *)s)[size]);
	if (c < 0)
		return (NULL);
	while (((char *)s)[i] != '\0')
	{
		if (((char *)s)[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	size_t	size;
	char	*s;

	size = ft_strlen(s1);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	if (size)
		ft_strlcpy(s, s1, size + 1);
	else
		*s = '\0';
	return (s);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s[start], len + 1);
	return (new);
}

int	ft_strncmp(char *s1, char *s2, int n)
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
	return (0);
}

int	check_quots(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
