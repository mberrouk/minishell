/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:22:38 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/08 18:54:19 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/shell.h"

int	symbol_case(char *line, t_lexer *ptr)
{
	int	i;

	i = 0;
	if (line[i] == '>')
		ptr->sym = APPEND_RE;
	else if (line[i] == '<')
		ptr->sym = HERE_DOC;
	ptr->arg = ft_realloc(ptr->arg, line[i++]);
	return (i);
}

int	tokenize_symbol(char *line, t_lexer *ptr)
{
	int	i;

	i = 0;
	ptr->sym = PIPE;
	if (line[i] == '|')
		ptr->arg = ft_realloc(ptr->arg, line[i++]);
	else if (line[i] == '>')
	{
		ptr->arg = ft_realloc(ptr->arg, line[i++]);
		ptr->sym = OUTPUT_RE;
		if (line[i] == '>')
			return (i += symbol_case(&line[i], ptr));
	}
	else if (line[i] == '<')
	{
		ptr->arg = ft_realloc(ptr->arg, line[i++]);
		ptr->sym = INPUT_RE;
		if (line[i] == '<')
			return (i += symbol_case(&line[i], ptr));
	}
	return (i);
}

int	hold_arg(char *line, t_lexer *ptr)
{
	int		i;
	char	quots;
	int		flg;

	flg = 0;
	i = 0;
	while (line[i])
	{
		if (!flg && (line[i] == '\'' || line[i] == '\"'))
		{
			quots = line[i];
			if (quots == '\'')
				ptr->squots = true;
			else
				ptr->dquots = true;
			flg = 1;
		}
		else if (flg && line[i] == quots)
			flg = 0;
		if (!flg && (line[i] == '>' || line[i] == '<' || line[i] == '|'
				|| ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')))
			break ;
		ptr->arg = ft_realloc(ptr->arg, line[i]);
		i++;
	}
	return (i);
}

void	lexical_analysis(char *line, t_lexer **lst)
{
	int			i;
	t_lexer		*ptr;

	*lst = NULL;
	ptr = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_withespace(line, i);
		if (line[i])
			lexer_lstadd_back(lst, lexer_lstnew(NULL));
		if (ptr)
			ptr = ptr->next;
		else
			ptr = *lst;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i += tokenize_symbol(&line[i], ptr);
		else
			i += hold_arg(&line[i], ptr);
	}
}
