/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/04 22:44:27 by mberrouk         ###   ########.fr       */
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


char    **join_double(char **fir, char *last)
{
    char **new;
    int len;
    int i;
    
    len = double_len(fir) + 1;
	if (!len)
		return (0x00);
    new = malloc(sizeof(char *) * (len + 1));
    if (!new)
	{
		free_double(fir);
		_print(2, "malloc failure\n");
        exit(errno);
	}
    i = 0;
    while (fir && fir[i])
    {
        new[i] = ft_strdup(fir[i]);
        if (!new[i])
        {
            return (0x00);
		}	    
		free(fir[i]);
        i++;
    }
	new[i] = ft_strdup(last);
	if (fir)
		free(fir);
	if (last)
		free(last);
	new[i + 1] = NULL;
	return (new);
}

