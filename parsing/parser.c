/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:31:45 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 03:40:36 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	**add_simple_cmd(char **ttmp, t_lexer *ptr, t_cmd *tmp);

t_file	*new_file(SymTok	type, char *name)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->fd = -1;
	new->next = NULL;
	new->name = name;
	new->type = type;
	return (new);
}

void	add_file(t_file **file_area, t_file *file)
{
	t_file	*ptr;

	ptr = *file_area;
	if (!ptr)
	{
		*file_area = file;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = file;
}

char	*handl_syntax(char *narg, char *arg, char quots, int n_qts)
{
	if (n_qts && n_qts % 2)
	{
		_print(2, "syntax error near unexpected token `%c'\n", quots);
		g_info.exit_status = 258;
		free(narg);
		free(arg);
		return (0x00);
	}
	free(arg);
	return (narg);
}

char	*handl_quots(char *arg)
{
	int		i;
	int		n_qts;
	char	quots;
	char	*narg;

	i = 0;
	n_qts = 0;
	quots = '\0';
	narg = ft_strdup("");
	while (arg[i])
	{
		if ((!quots || quots == arg[i]) && (arg[i] == '\'' || arg[i] == '\"'))
		{
			if (!quots)
				quots = arg[i];
			else
				quots = '\0';
			n_qts++;
		}
		else if (arg[i] && arg[i] != quots)
			narg = ft_realloc(narg, arg[i]);
		i++;
	}
	return (handl_syntax(narg, arg, quots, n_qts));
}

t_lexer	*hold_args(t_cmd **head, t_lexer *ptr, t_cmd *tmp, char **env)
{
	char	**ttmp;
	int		i;

	i = 0;
	ttmp = NULL;
	if (ptr->sym != HERE_DOC && ft_strchr(ptr->arg, '$'))
		ptr->arg = pars_arg_expan(ptr->arg, env);
	if (check_quots(ptr->arg))
		ptr->arg = handl_quots(ptr->arg);
	else
		ttmp = ultra_split(ptr->arg, " \t\n\r");
	if (!(ptr->arg))
	{
		clean_parss(head);
		return (0x00);
	}
	if (ptr->sym != SIMPLE_CMD)
		add_file(&(tmp->file), new_file(ptr->sym, ft_strdup(ptr->arg)));
	else
		tmp->cmd = add_simple_cmd(ttmp, ptr, tmp);
	return (ptr->next);
}
