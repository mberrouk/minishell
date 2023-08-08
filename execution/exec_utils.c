/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:32:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 16:58:10 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"

int	builtin_status(char **str)
{
	if (!str)
		return (-1);
	if (!ft_strncmp("cd", str[0], 3)
		|| !ft_strncmp("pwd", str[0], 4)
		|| !ft_strncmp("echo", str[0], 5)
		|| !ft_strncmp("exit", str[0], 5)
		|| !ft_strncmp("env", str[0], 4)
		|| !ft_strncmp("unset", str[0], 6)
		|| !ft_strncmp("export", str[0], 7))
		return (0);
	return (-1);
}

void	not_found(char *parm)
{
	write(STDERR_FILENO, "minishell: ", 12);
	if (parm && *parm)
		write(STDERR_FILENO, parm, ft_strlen(parm));
	write(STDERR_FILENO, ": command not found\n", 21);
	free(parm);
	exit(127);
}

void	puterr(char *str)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		exit(g_info.exit_status);
	}
	else
	{
		perror("Error");
		exit(g_info.exit_status);
	}
}

char	**find_path(char **env)
{
	char	**paths;
	int		i;
	int		j;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (!path[j])
		{
			paths = ft_split(&env[i][j], ':');
			return (paths);
		}		
		i++;
	}
	return (NULL);
}

int	ft_lstsize_s(char **lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst[i])
	{
		i++;
	}
	return (i);
}
