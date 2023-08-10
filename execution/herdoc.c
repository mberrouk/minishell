/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/10 23:36:08 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include "../include/shell.h"

void	handle_doc_sigint(int signal)
{
	(void)signal;
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
		if ((!*line && !*delm) || (line && *line && ft_strcmp(line, delm) == 0))
			break ;
		if (line && *line)
		{
			line = expan_in_dquots(line, env);
			_print(tab[1], line);
			_print(tab[1], "\n");
		}
		if (line)
			free(line);
	}
	if (line)
		free(line);
}

void	handle_append_herdoc(t_cmd *data, char *delm, char **env)
{
	pid_t	pid;
	int		tab[2];

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
		while (wait(0) > 0);
		close(tab[1]);
		if (data->input > 0)
			close(data->input);
		data->input = tab[0];
	}
}

void	open_doc(t_cmd *cmd, char **env)
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
				handle_append_herdoc(cmd, file->name, env);
			file = file->next;
		}
		cmd = cmd->next;
	}
}
