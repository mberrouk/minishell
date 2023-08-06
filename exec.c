/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:15:47 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/06 19:16:29 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <unistd.h>
#include "include/shell.h"

int size_cmds(t_cmd *cmds)
{
    int i;
    
    i = 0;
	while(cmds)
	{
		i++;
		cmds = cmds->next;
	}
    return (i);
}

void execution(t_cmd   *cmds, char **env)
{
    pid_t   pid;
    int     size;
//  int     status;
    int i;
    int **pipes;
    (void)env;
    int fd_inp;
    int fd_out;
    
    size = size_cmds(cmds);
    i = 0;
    fd_inp = 0;
    fd_out = 1;
    if (!cmds)
        _print(2, "error");
    pipes = (int **) malloc(sizeof(int *) * (size - 1));
    if (!pipes)
    {
        _print(2, "Pipes allocation errors");
        g_info.exit_status = 1;
        exit(1);
    }
    while (i < size - 1)
    {
        pipes[i] = (int *) malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            _print(2, "Pipes[%d] allocation errors", i);
            g_info.exit_status = 1;
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < size - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            _print(2, "Pipes[%d] errors", i);
            g_info.exit_status = 1;
            exit(1);
        }
        i++;
    }
    if (size == 1)
        builtins_main(&g_info.g_env, cmds);
    while (cmds)
    {
        
    }
    i = 0;
    while (i < size)
    {
        pid = fork();
        if (pid == 0)
        {
            
        }
        
    }
}
