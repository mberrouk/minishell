/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:15 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/09 01:24:52 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	lexer_lstadd_back(t_lexer **lst, t_lexer *node)
{
	t_lexer	*ptr;

	if (!lst)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = node;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = node;
}

t_lexer	*lexer_lstnew(void *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->arg = content;
	new->squots = false;
	new->dquots = false;
	new->sym = SIMPLE_CMD;
	return (new);
}

void	parser_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (!lst)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_cmd	*parser_lstnew(void *content)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->cmd = content;
	new->type = SIMPLE_CMD;
	new->input = -1;
	new->file = NULL;
	return (new);
}
