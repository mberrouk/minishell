/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:28:56 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/12 23:52:29 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	hold_args2(t_lexer *ptr, t_cmd *tmp, char **ttmp, int drp)
{
	if (ptr->sym != SIMPLE_CMD)
	{
		if (ptr->sym == HERE_DOC && drp && ptr->arg)
			add_file(&(tmp->file), new_file(ptr->sym + 2, \
			ft_strdup(ptr->arg), 1));
		else if ((ttmp && ttmp[1]) || ((!drp) && !*(ptr->arg)))
			add_file(&(tmp->file), new_file(ptr->sym, ft_strdup(ptr->arg), 1));
		else
			add_file(&(tmp->file), new_file(ptr->sym, ft_strdup(ptr->arg), 0));
	}
	else
		tmp->cmd = add_simple_cmd(ttmp, ptr, tmp);
}

t_lexer	*parse_lexer_data(t_cmd **head, t_lexer *ptr, t_cmd *cmd, char **env)
{
	t_cmd		*tmp;
	t_SymTok	token;

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
			_print(2, "syntax error near unexpected token `%s'\n", ptr->arg);
		g_info.exit_status = 258;
		clean_parss(head);
		return (0x00);
	}
	ptr->sym = token;
	return (hold_args(head, ptr, tmp, env));
}

int	check_token(t_lexer *ptr, t_lexer *data, t_cmd **cmd)
{
	if ((ptr && ptr->sym == PIPE && ptr == data)
		|| ((ptr && ptr->sym == PIPE)
			&& (!ptr->next || ptr->next->sym == PIPE)))
	{
		_print(2, "syntax error near unexpected token `%s'\n", ptr->arg);
		g_info.exit_status = 258;
		clean_parss(cmd);
		return (1);
	}
	return (0);
}

t_cmd	*get_the_next(t_cmd **cmd, t_cmd *tmp)
{
	parser_lstadd_back(cmd, parser_lstnew(NULL));
	if (tmp)
	{
		g_info.exit_status = 0;
		tmp = tmp->next;
	}
	else
		tmp = *cmd;
	return (tmp);
}

void	init_parse(t_cmd **cmd, char *line, char *env[])
{
	t_lexer	*data;
	t_lexer	*ptr;
	t_cmd	*tmp;

	data = NULL;
	if (!line || !line[skip_withespace(line, 0)])
		return ;
	add_history(line);
	lexical_analysis(line, &data);
	ptr = data;
	tmp = NULL;
	while (ptr)
	{
		if (check_token(ptr, data, cmd))
			break ;
		else
			tmp = get_the_next(cmd, tmp);
		if (ptr->sym == PIPE)
			ptr = ptr->next;
		while (ptr && ptr->sym != PIPE)
			ptr = parse_lexer_data(cmd, ptr, tmp, env);
	}
	clean_lexer(data);
}
