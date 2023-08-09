/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/09 04:35:47 by mberrouk         ###   ########.fr       */
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

	while (1)
	{
		line = readline(">");
		if (line == NULL)
			exit(-1);
		else
		{
			if (ft_strcmp(line, delm) == 0)
			{
				free(line);
				break ;
			}
		}
		line = expan_in_dquots(line, env);
		_print(tab[1], line);
		_print(tab[1], "\n");
		free(line);
	}
}

void	handle_append_herdoc(t_cmd *data, char *delm, char **env)
{
	pid_t	pid;
	int		tab[2];

	pipe(tab);
	pid = fork();
	if (pid == 0)
	{
		sign_herdoc();
		her_doc_loop(tab, delm, env);
		close(tab[0]);
		close(tab[1]);
		exit(0);
	}
	else
	{
		wait(0);
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
				printf("%d\n", cmd->input);
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
