/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:38:11 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/08 00:38:30 by hoakoumi         ###   ########.fr       */
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

    if (data->file->type == HERE_DOC)
        data->type = data->file->type;
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
                    return ;
                }
                ft_putstr_fd(line, tab[1]);
	            ft_putstr_fd("\n", tab[1]);
	            free(line);
            }
                
         }
    }
    wait(0);
	close(tab[1]);
	free(line);
}
