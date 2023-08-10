/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 04:24:19 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/10 04:26:43 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

typedef enum symbolicToken
{
	PIPE,
	INPUT_RE,
	OUTPUT_RE,
	APPEND_RE,
	HERE_DOC,
	SIMPLE_CMD
}	t_SymTok;

typedef struct s_lexer
{
	t_SymTok		sym;
	char			*arg;
	bool			squots;
	bool			dquots;
	struct s_lexer	*next;
}	t_lexer;

#endif
