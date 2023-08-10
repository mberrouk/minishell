/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:25:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 15:55:21 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/minishell.h"
#include <dirent.h>

int	handle_input_redirection(t_cmd *data, t_file *file, int *fd_inp)
{
	(void)data;
	if (file->type == INPUT_RE)
	{
		if (*fd_inp != 0)
			close(*fd_inp);
		*fd_inp = open(file->name, O_RDONLY);
		if (*fd_inp == -1 || !file->name)
		{
			_print(2, "minishell: ");
			if (!file->name || !*file->name)
				_print(2, "ambiguous redirect\n");
			else
				perror(file->name);
			g_info.exit_status = 1;
			return (1);
		}
	}
	return (0);
}

int	handle_output_redirection(t_cmd *data, t_file *file, int *fd_oup)
{
	if (file->type == OUTPUT_RE)
	{
		data->type = file->type;
		if (*fd_oup != 1)
			close(*fd_oup);
		*fd_oup = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_oup == -1)
		{
			_print(2, "minishell: ");
			if (!file->name || !*file->name)
				_print(2, "ambiguous redirect\n");
			else
				perror(file->name);
			g_info.exit_status = 1;
			return (1);
		}
	}
	return (0);
}

int	handle_append_redirection(t_cmd *data, t_file *file, int *fd_app)
{
	if (file->type == APPEND_RE)
	{
		data->type = file->type;
		if (*fd_app != -1)
			close(*fd_app);
		*fd_app = open(file->name, O_APPEND | O_CREAT | O_RDWR, 0664);
		if (*fd_app == -1)
		{
			_print(2, "minishell: ");
			if (!file->name || !*file->name)
				_print(2, "ambiguous redirect\n");
			else
				perror(file->name);
			g_info.exit_status = 1;
			return (1);
		}
	}
	return (0);
}

void	han_buil_comnds(t_cmd *data, char **cmds, char **path, char **env)
{
	char	*cmd;
	DIR		*dir;

	if (cmds && *cmds && builtin_status(data->cmd) != -1)
	{
		builtins_main(&g_info.g_env, data);
		exit(g_info.exit_status);
	}
	else if (cmds && *cmds)
	{
		g_info.exit_status = 0;
		if (cmds && cmds[0] && (cmds[0][0] == '/' || cmds[0][0] == '.'))
			cmd = cmds[0];
		else
			cmd = ft_access(path, cmds[0]);
		if (!cmd)
			not_found(cmds[0]);
		if (execve(cmd, cmds, env) == -1)
		{
			if (errno == 2)
			{
				perror("minishell");
				exit(127);
			}
			if (errno == 13)
			{
				dir = opendir(cmd);
				if (dir)
					_print(2, "minishell: is a directory\n");
				else
					perror("minishell");
				exit(126);
			}
		}
	}
	else
		exit(g_info.exit_status);
}

void	setup_pipes(int ifd, int *pip)
{
	if (ifd > 0)
	{
		if (dup2(ifd, STDIN_FILENO) == -1)
			puterr("Error");
	}
	if (ifd == -1)
		return ;
	if (pip[1] > 1)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
		{
			puterr("Error");
			if (pip[1] == -1)
				close(ifd);
		}
	}
	if (pip[1] > 1)
		close(pip[1]);
	if (ifd > 0)
		close(ifd);
	if (pip[0] > 0)
		close(pip[0]);
}
