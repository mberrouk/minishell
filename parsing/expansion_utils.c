/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:54:38 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/05 07:03:52 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	sp_stay(char ch)
{
	char	*sp_char;

	sp_char = " \t\n\f\v\r\b\\`~%^&()-=+[]{};:/.>,<#";
	if (ft_strchr(sp_char, ch))
		return (1);
	return (0);
}

int	check_sp_char(char c)
{
	char	*sp_char;

	sp_char = " \t\n\f\v\r\b\"'\\`~!@#$%^&*()-=+[]{};:/?.>,<0123456789";
	if (ft_strchr(sp_char, c))
		return (1);
	return (0);
}

int	sp_remove(char ch)
{
	char	*sp_char;

	sp_char = "@?*0123456789";
	if (ft_strchr(sp_char, ch))
		return (1);
	return (0);
}

int	sp_at_end(char ch)
{
	char	*sp_char;

	sp_char = " \t\n\f\v\r\b\"\'\\`~!@#$%^&*()-=+[]{};:/?.>,<";
	if (ft_strchr(sp_char, ch))
		return (1);
	return (0);
}

int	handl_spchar_cases(char *arg, char **value)
{
	int	len;

	len = 0;
	if (arg[len] == '?')
		*value = ft_strjoin(*value, ft_itoa(g_info.exit_status));
	if (sp_remove(arg[len]))
		len++;
	else
	{
		len = len_to_spchar(arg);
		*value = ft_strjoin(*value, ft_substr(arg, 0, len));
	}
	return (len);
}
