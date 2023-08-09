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
}	SymTok;

typedef struct s_lexer
{
	SymTok			sym;
	char			*arg;
	bool			squots;
	bool			dquots;
	struct s_lexer	*next;
}	t_lexer;
#endif
