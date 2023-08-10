/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 02:56:06 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/minishell.h"

void	setup_pipe_fds(int *pip_fds, t_exec *fd, t_cmd *data)
{
	pip_fds[1] = 1;
	pip_fds[0] = 0;
	if (data->next)
	{
		if (pipe(pip_fds) == -1)
			puterr(NULL);
	}
	else
		pip_fds[1] = fd->fd_oup;
	execute_command(*fd, pip_fds, data, data->cmd);
	if (fd->fd_inp != 0)
		close(fd->fd_inp);
	if (pip_fds[1] != 1)
		close(pip_fds[1]);
}

void	execute_commands(t_cmd *data, int fd_inp, char **path, char **env)
{
	int		pip_fds[2];
	t_exec	fd;

	fd.fd_app = -1;
	fd.env = env;
	fd.path = path;
	fd.fd_inp = fd_inp;
	while (data != NULL)
	{
		fd.fd_oup = 1;
		if (!data->cmd && !data->file)
			return ;
		setup_pipe_fds(pip_fds, &fd, data);
		fd.fd_inp = pip_fds[0];
		data = data->next;
	}
	if (fd.fd_inp != 0)
		close(fd.fd_inp);
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
		g_info.exit_status = status;
		free_double(path);
	}
}
