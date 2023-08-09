/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:22 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/04 22:44:27 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

/**
 * is_sep - Checks if a character is a separator
 * @s: The character to be checked
 * @sp: The separator character
 *
 * Return: 1 if the character is a separator, 0 otherwise
 */
static int	is_sep(char s, char sp)
{
	if (sp == s)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}


/**
 * count_dup - Counts and duplicates substrings based on a separator
 * @s: The array of strings to store the substrings
 * @str: The input string
 * @c: The separator character
 *
 * Return: The array of strings with the duplicated substrings
 */
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


/**
 * ft_split - Splits a string into an array of substrings based on a separator
 * @s: The input string
 * @c: The separator character
 *
 * Return: The array of substrings, or NULL on failure
 */
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
