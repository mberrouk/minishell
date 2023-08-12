/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 03:03:12 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include "../include/shell.h"

void	handle_doc_sigint(int signal)
{
	(void)signal;
	write(STDIN_FILENO, "\n", 1);
	exit(1);
}

void	sign_herdoc(void)
{
	signal(SIGINT, handle_doc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	her_doc_loop(int *tab, char *delm, char **env)
{
	char	*line;

	sign_herdoc();
	while (1)
	{
		line = readline("> ");
		if (!line || (!*line && !*delm) || (line && *line && ft_strcmp(line, delm) == 0))
			break ;
		line = expan_in_dquots(line, env);
		_print(tab[1], line);
		_print(tab[1], "\n");
		free(line);
	}
	if (line)
		free(line);
}

int	handle_append_herdoc(t_cmd *data, char *delm, char **env)
{
	pid_t	pid;
	int		tab[2];
	int		status;

	pipe(tab);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		her_doc_loop(tab, delm, env);
		close(tab[0]);
		close(tab[1]);
		free_double(env);
		free(delm);
		exit(0);
	}
	else
	{
		waitpid(pid, &(status), 0);
		if (WIFEXITED(status))
		{
			g_info.exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status)) 
            g_info.exit_status = WTERMSIG(status) + 128;
		close(tab[1]);
		if (data->input > 0)
			close(data->input);
		data->input = tab[0];
	}
	return (g_info.exit_status);
}

int	open_doc(t_cmd *cmd, char **env)
{
	t_file	*file;

	while (cmd)
	{
		file = cmd->file;
		while (file)
		{
			if (file->type == INPUT_RE && cmd->input > 0)
			{
				close(cmd->input);
				cmd->input = -1;
			}
			else if (file->type == HERE_DOC)
				if(handle_append_herdoc(cmd, file->name, env))
					return (1);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
