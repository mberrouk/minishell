/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 01:52:28 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include "include/shell.h"

void	handle_doc_sigint(int signal)
{
	(void)signal;
	exit(1);
}

void handle_append_herdoc(t_cmd *data, char *delm)
{
    pid_t pid;
    char  *line;
    int tab[2];

    pipe(tab);
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, handle_doc_sigint);
		signal(SIGQUIT, SIG_IGN);
        while(1)
        {
            line = readline(">");
			if (line == NULL)
				exit(0);
            else
            {
                if (ft_strcmp(line, delm) == 0)
                {
                    free(line);
                    break ;
                }
                _print(tab[1], line);
	            _print(tab[1], "\n");
	            free(line);
            }
        }
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

void    open_doc(t_cmd *cmd)
{
    t_file  *file;
    
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
                handle_append_herdoc(cmd, file->name);
            file = file->next;
        }
        printf("%d\n", cmd->input);
        cmd = cmd->next;    
    }

}
