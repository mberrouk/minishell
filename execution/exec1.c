/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:27:46 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/13 00:48:09 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include "../include/minishell.h"

char	*ft_access(char **paths, char *cmd)
{
	char	*new;
	char	*v_cmd;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!new)
		return (NULL);
	new[0] = '/';
	ft_strlcpy(&new[1], cmd, ft_strlen(cmd) + 1);
	while (paths && paths[i])
	{
		v_cmd = ft_strjoin(paths[i], ft_strdup(new));
		if (!access(v_cmd, X_OK))
		{
			free(new);
			return (v_cmd);
		}
		free(v_cmd);
		i++;
	}
	free(new);
	return (NULL);
}

void	cat_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	manage_fd(t_exec *fd, t_cmd *data, int *pip)
{
	if (fd->fd_oup > 1)
	{
		if (pip[1] > 1)
			close(pip[1]);
		pip[1] = fd->fd_oup;
	}
	if (data->type == APPEND_RE)
	{
		if (fd->fd_oup != 1)
			close(fd->fd_oup);
		if (pip[1] > 1)
			close(pip[1]);
		pip[1] = fd->fd_app;
	}
	if (data->input > 0)
	{
		if (fd->fd_inp > 0)
			close(fd->fd_inp);
		fd->fd_inp = data->input;
	}
}

int	execute_command(t_exec fd, int *pip, t_cmd *data, char **cmds)
{
	signal(SIGINT, SIG_IGN);
	data->pid = fork();
	if (data->pid == 0)
	{
		signal(SIGINT, cat_handle_sigint);
		signal(SIGQUIT, SIG_DFL);
		if (open_fd_file(data, &fd.fd_inp, &fd.fd_oup, &fd.fd_app))
		{
			if (fd.fd_inp > 0)
				close(fd.fd_inp);
			fd.fd_inp = 0;
			data = data->next;
			exit(1);
		}
		manage_fd(&fd, data, pip);
		setup_pipes(fd.fd_inp, pip);
		han_buil_comnds(data, cmds, fd.path, fd.env);
	}
	else if (data->pid < 0)
		return (fork_err(fd, pip));
	return (0);
}

int	open_fd_file(t_cmd *data, int *fd_inp, int *fd_oup, int *fd_app)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		if (handle_input_redirection(data, tmp, fd_inp))
			return (1);
		if (handle_output_redirection(data, tmp, fd_oup))
			return (1);
		if (handle_append_redirection(data, tmp, fd_app))
			return (1);
		tmp = tmp->next;
	}
	clean_file(data->file);
	return (0);
}
