/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 22:08:36 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/minishell.h"

int	setup_pipe_fds(int *pip_fds, t_exec *fd, t_cmd *data)
{
	int	flag;

	flag = 0;
	pip_fds[1] = 1;
	pip_fds[0] = 0;
	if (data->next)
	{
		if (pipe(pip_fds) == -1)
		{
			perror("Error");
			return (1);
		}
	}
	else
		pip_fds[1] = fd->fd_oup;
	if (execute_command(*fd, pip_fds, data, data->cmd))
		return (1);
	if (fd->fd_inp != 0)
		close(fd->fd_inp);
	if (pip_fds[1] != 1)
		close(pip_fds[1]);
	return (0);
}

int	execute_commands(t_cmd *data, int fd_inp, char **path, char **env)
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
			return (0);
		if (setup_pipe_fds(pip_fds, &fd, data))
		{
			if (pip_fds[0])
				close(pip_fds[0]);
			return (1);
		}
		fd.fd_inp = pip_fds[0];
		data = data->next;
	}
	if (fd.fd_inp != 0)
		close(fd.fd_inp);
	return (0);
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
	int		drp;

	if (!data)
		return ;
	if (!data->next && data->cmd && (strcmp(*data->cmd, "exit") == 0
			|| ((builtin_status(data->cmd) != -1) \
			&& !data->file)))
		builtins_main(&g_info.g_env, data);
	else
	{
		path = find_path(env);
		open_doc(data, env);
		drp = execute_commands(data, 0, path, env);
		while (data)
		{
			waitpid(data->pid, &status, 0);
			data = data->next;
		}
		if (WIFEXITED(status))
		{	if (!drp)
				g_info.exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status)) 
            g_info.exit_status = WTERMSIG(status) + 128;
		free_double(path);
	}
}
