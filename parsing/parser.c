/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:31:45 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/05 07:22:56 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/shell.h"

t_file *new_file(SymTok	type, char *name)
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

t_lexer	*hold_args(t_cmd **head, t_lexer *ptr, t_cmd *tmp, char **env)
{
	if (ptr->sym != HERE_DOC && ft_strchr(ptr->arg, '$'))
		ptr->arg = pars_arg_expan(ptr->arg, env);
	if (check_quots(ptr->arg))
		ptr->arg = handl_quots(ptr->arg);
	if (!(ptr->arg))
	{
		/** dont check it her !?  **/
		//printf("ambiguous redirect\n");
		clean_parss(head);
		return (0x00);
	}
	if (ptr->sym != SIMPLE_CMD)
		add_file(&(tmp->file), new_file(ptr->sym, ft_strdup(ptr->arg)));
	else
		tmp->cmd = join_double(tmp->cmd, ft_strdup(ptr->arg));
	return (ptr->next);
}

t_lexer	*parse_lexer_data(t_cmd **head, t_lexer *ptr, t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	SymTok	token;

	tmp = cmd;
	token = ptr->sym;
	if (token == SIMPLE_CMD)
		return (hold_args(head, ptr, tmp, env));
	ptr = ptr->next;
	if (!ptr || ptr->sym != SIMPLE_CMD)
	{
		if (!ptr)
			_print(2, "syntax error near unexpected token `%s'\n", "newline");
		else
			_print(2, "1 syntax error near unexpected token `%s'\n", ptr->arg);
		g_info.exit_status = 258;
		clean_parss(head);
		return (0x00);
	}
    ptr->sym = token;
    return (hold_args(head, ptr, tmp, env));
}


void	init_parse(t_cmd **cmd, char *line, char *env[])
{
	t_lexer	*data;
	t_lexer	*ptr;
	t_cmd	*tmp;

	data = NULL;
	if (!line || !line[skip_withespace(line, 0)])
		return ;
	lexical_analysis(line, &data);
	ptr = data;
	tmp = NULL;
	while (ptr)
	{
		if ((ptr && ptr->sym == PIPE && ptr == data)
			|| ((ptr && ptr->sym == PIPE)
				&& (!ptr->next || ptr->next->sym == PIPE)))
		{
			_print(2, "syntax error near unexpected token `%s'\n", ptr->arg);
			g_info.exit_status = 258;
			clean_parss(cmd);
			break ;
		}
		else
		{
			parser_lstadd_back(cmd,  parser_lstnew(NULL));
			if (tmp)
				tmp = tmp->next;
			else 
				tmp = *cmd;
		}
		if (ptr->sym == PIPE)
			ptr = ptr->next;
		while (ptr && ptr->sym != PIPE)
			ptr = parse_lexer_data(cmd, ptr, tmp, env);
	}
	clean_lexer(data);
}
