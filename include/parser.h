#ifndef PARSER_H
#define PARSER_H

#include "../include/lexer.h"

typedef struct s_file
{
	SymTok			type;
	char			*name;
	int				fd;			/** the file descripti*/
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	SymTok			type;
	char			**cmd; 
	t_file			*file;
	struct s_cmd	*next;
}	t_cmd;

char	*pars_expan(t_lexer *data, char **env);

#endif


