#ifndef LEXER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_H
typedef enum
{
	ID,
	BINARY,
	SYMBOL,
	PIN,
	MACRO_NAME,
	NUMBER,
	END_OF_FILE,  // cant use EOF because EOF already exists as a macro.
} token_type;

typedef struct
{
	char* text;
	token_type type;
	size_t line, col;
} token_t;

typedef struct
{
	char* source;
	size_t position;
	size_t line, col;
} lexer_t;

#define current lexer->source[lexer->position]

#define next           \
	++lexer->position; \
	++lexer->col

token_t lex(lexer_t* lexer);

#define token_type_to_string(type)                                       \
	(((char*[]){"ID", "BINARY", "SYMBOL", "PIN", "MACRO_NAME", "NUMBER", \
				"END_OF_FILE"})[type])

#endif
