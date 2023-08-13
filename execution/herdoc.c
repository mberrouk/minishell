/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/13 00:57:53 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	her_doc_loop(int *tab, char *delm, char **env, t_SymTok type)
{
	char	*line;

	sign_herdoc();
	while (1)
	{
		line = readline("> ");
		if ((line && *line && ft_strcmp(line, delm) == 0)
			|| !line || (!*line && !*delm))
			break ;
		if (type == HERE_DOC)
			line = expan_in_dquots(line, env);
		_print(tab[1], line);
		_print(tab[1], "\n");
		free(line);
	}
	if (line)
		free(line);
}

int	handle_append_herdoc(t_cmd *data, char *delm, char **env, t_SymTok type)
{
	pid_t	pid;
	int		tab[2];

	pipe(tab);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		her_doc_loop(tab, delm, env, type);
		close(tab[0]);
		close(tab[1]);
		free_double(env);
		free(delm);
		exit(0);
	}
	else
		wait_child(pid, data, tab);
	return (g_info.exit_status);
}

int	open_doc(t_cmd *cmd, char **env)
{
	t_file	*file;

	count_herdoc(cmd->file);
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
			else if (file->type == HERE_DOC || file->type == HERE_DOC + 2)
				if (handle_append_herdoc(cmd, file->name, env, file->type))
					return (1);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
