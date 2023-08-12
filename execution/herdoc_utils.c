/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 05:08:50 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/12 05:41:04 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	count_herdoc(t_file *file)
{
	int	num;

	num = 0;
	while (file)
	{
		if (file->type == HERE_DOC)
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
