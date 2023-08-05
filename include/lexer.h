#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

/**
 * enum SymTok - Represents different symbolic tokens for bash operators
 * @PIPE: Represents the pipe operator '|'
 * @INPUT_RE: Represents the input redirection operator '<'
 * @OUTPUT_RE: Represents the output redirection operator '>'
 * @APPEND_RE: Represents the append redirection operator '>>'
 * @HERE_DOC: Represents the here document operator '<<'
 *
 * This enum defines symbolic tokens for various bash operators used for input/output redirection and command chaining.
 * Each token represents a specific operator and can be used to identify and handle different operations in a program.
 */
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
