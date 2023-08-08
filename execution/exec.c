/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 16:54:57 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/minishell.h"

void	setup_pipe_fds(int *pip_fds, int fd_oup, int fd_app, int *fd_inp, t_cmd *data, char **path, char **env)
{
	pip_fds[1] = 1;
	pip_fds[0] = 0;
	if (data->type == APPEND_RE)
	{
		if (fd_oup != 1)
			close(fd_oup);
		fd_oup = fd_app;
	}
	if (data->next)
	{
		if (pipe(pip_fds) == -1)
			puterr(NULL);
		if (fd_oup > 1)
		{
			close(pip_fds[1]);
			pip_fds[1] = fd_oup;
		}
	}
	else
		pip_fds[1] = fd_oup;
	if (data->input > 0)
	{
		if (*fd_inp > 0)
			close(*fd_inp);
		*fd_inp = data->input;
	}
	execute_command(*fd_inp, pip_fds, data, data->cmd, path, env);
	if (*fd_inp != 0)
		close(*fd_inp);
	if (pip_fds[1] != 1)
		close(pip_fds[1]);
}

void	execute_commands(t_cmd *data, int fd_inp, char **path, char **env)
{
	int	pip_fds[2];
	int	fd_oup;
	int	fd_app;

	fd_app = -1;
	while (data != NULL)
	{
		fd_oup = 1;
		if (!data->cmd && !data->file)
			return ;
		open_fd_file(data, &fd_inp, &fd_oup, &fd_app);
		setup_pipe_fds(pip_fds, fd_oup, fd_app, &fd_inp, data, path , env);
		fd_inp = pip_fds[0];
		data = data->next;
	}
	if (fd_inp != 0)
		close(fd_inp);
}

void	cmds(t_cmd *data, int fd_inp, char **path, char **env)
{
	execute_commands(data, fd_inp, path, env);
}

int	size_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	exec_cmds(t_cmd *data, int status, char **env)
{
	char	**path;

	if (!data)
		return ;
	if (builtin_status(data->cmd) != -1 && (size_cmds(data) == 1))
		builtins_main(&g_info.g_env, data);
	else
	{
		path = find_path(env);
		open_doc(data, env);
		cmds(data, 0, path, env);
		while (wait(&status) > 0)
			;
		status = WEXITSTATUS(status);
		free_double(path);
	}
}
