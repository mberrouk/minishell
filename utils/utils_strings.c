/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:35:17 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 04:19:58 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	copy_str(char *new, char *s1, char *s2);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str || !*str)
		return (0);
	while (str && str[len])
		len++;
	return (len);
}

int	skip_withespace(char *cmd, int i)
{
	if (!cmd)
		return (0);
	while (cmd[i] && (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13)))
		i++;
	return (i);
}

char	*ft_realloc(char *str, char c)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(str) + 2;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (print_err("malloc failed\n"));
	i = 0;
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (str)
		free(str);
	return (new);
}

int	ft_strlcpy(char *dest, char *src, int dstsize)
{
	int	i;
	int	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (src && dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
		return (src_size);
	dest[i] = '\0';
	return (src_size);
}



char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new)
		return (NULL);
	copy_str(new, s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	s1 = NULL;
	s2 = NULL;
	return (new);
}
