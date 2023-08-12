/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 05:08:50 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 22:25:18 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	fork_err(t_exec fd, int *pip)
{
	perror("minishell: fork");
	g_info.exit_status = 1;
	if (fd.fd_inp > 0)
		close(fd.fd_inp);
	if (fd.fd_oup > 0)
		close(fd.fd_oup);
	if (pip[0] > 2)
		close(pip[0]);
	if (pip[1] > 2)
		close(pip[1]);
	return (1);
}

void	count_herdoc(t_file *file)
{
	int	num;

	num = 0;
	while (file)
	{
		if (file->type == HERE_DOC
			|| file->type == HERE_DOC + 2)
			num++;
		if (num == 17)
		{
			_print(2, "minishell: maximum here-document count exceeded\n");
			exit(2);
		}
		file = file->next;
	}
}

void	wait_child(pid_t pid, t_cmd *data, int *tab)
{
	int	status;

	waitpid(pid, &(status), 0);
	g_info.exit_status = WEXITSTATUS(status);
	close(tab[1]);
	if (data->input > 0)
		close(data->input);
	if (!g_info.exit_status)
		data->input = tab[0];
	else
		close(tab[0]);
}
