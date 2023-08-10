/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:32:14 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 20:48:16 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"

#include <dirent.h>

void	chois_exit_s(char *arg)
{
	DIR		*dir;

	if (errno == 2)
	{
		perror("minishell");
		exit(127);
	}
	if (errno == 13)
	{
		dir = opendir(arg);
		if (dir)
			_print(2, "minishell: is a directory\n");
		else
		{
			errno = 13;
			perror("minishell");
		}
		exit(126);
	}
}

int	builtin_status(char **str)
{
	if (!str || !*str)
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
