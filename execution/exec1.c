/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:27:46 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 18:39:49 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
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

void	execute_child(int ifd, int *pip, t_cmd *data, char **cmds, char **path, char **env)
{
	setup_pipes(ifd, pip);
	handle_builtin_commands(data, cmds, path, env);
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

void	execute_command(int ifd, int *pip, t_cmd *data, char **cmds, char **path, char **env) 
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, cat_handle_sigint);
		signal(SIGQUIT, cat_handle_sigint);
		execute_child(ifd, pip, data, cmds, path, env);
	}
	else if (pid < 0)
		puterr(NULL);
}

void	open_fd_file(t_cmd *data, int *fd_inp, int *fd_oup, int *fd_app)
{
	t_file	*tmp;

	tmp = data->file;
	while (tmp)
	{
		handle_input_redirection(data, tmp, fd_inp);
		handle_output_redirection(data, tmp, fd_oup);
		handle_append_redirection(data, tmp, fd_app);
		tmp = tmp->next;
	}
}
