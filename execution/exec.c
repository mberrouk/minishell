/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 17:54:33 by mberrouk         ###   ########.fr       */
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
	if (!data->next && data->cmd && (strcmp(*data->cmd, "exit") == 0
			|| ((builtin_status(data->cmd) != -1) \
			&& !data->file)))
		builtins_main(&g_info.g_env, data);
	else
	{
		g_info.exit_status = 0;
		path = find_path(env);
		open_doc(data, env);
		execute_commands(data, 0, path, env);
		while (wait(&status) > 0)
			;
		status = WEXITSTATUS(status);
		g_info.exit_status = status;
		free_double(path);
	}
}
