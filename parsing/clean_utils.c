/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:07:03 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 14:23:24 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	clean_file(t_file *file)
{
	t_file	*tmp;
	t_file	*prev;

	tmp = file;
	while (tmp)
	{
		if (tmp->name)
			free(tmp->name);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	file = NULL;
}

void	clean_parss(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*prev;

	tmp = *cmd;
	while (tmp)
	{
		free_double(tmp->cmd);
		clean_file(tmp->file);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	*cmd = NULL;
}

void	clean_lexer(t_lexer *data)
{
	t_lexer	*tmp;

	while (data)
	{
		if (data->arg)
			free(data->arg);
		tmp = data;
		data = data->next;
		free(tmp);
	}
	data = NULL;
}
