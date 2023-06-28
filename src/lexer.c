#include "lexer.h"

token_t lex(lexer_t* lexer)
{
	// using the null terminator isnt always reliable.
	// if a mistake is made we could accidentally skip the 0
	if (lexer->position >= strlen(lexer->source))
	{
		return (token_t){
			0,
			END_OF_FILE,
		};
	}
	if (current == ' ' || current == '\t')
	{
		next;
		return lex(lexer);
	}
	if (current == '\n')
	{
		++lexer->line;
		++lexer->position;
		lexer->col = 0;
		return lex(lexer);
	}
	if (current >= 'a' && current <= 'z' || current >= 'A' && current <= 'Z' ||
		current == '_')
	{
		size_t start = lexer->position;
		while (current >= 'a' && current <= 'z' ||
			   current >= 'A' && current <= 'Z' || current == '_' ||
			   current >= '0' && current <= '9')
		{
			next;
		}
		size_t length = lexer->position - start;

		char* end_result = malloc(length + 1);
		memset(end_result, 0, length + 1);

		for (size_t i = 0; i < length; ++i)
		{
			end_result[i] = lexer->source[start + i];
		}

		if (lexer->source[lexer->position] == '!')
		{
			next;
			return (token_t){end_result, MACRO_NAME, lexer->line, lexer->col};
		}

		return (token_t){end_result, ID, lexer->line, lexer->col};
	}
	if (current == '0' || current == '1')
	{
		char* str = malloc(2);
		str[1] = 0;
		str[0] = current;
		next;
		return (token_t){str, BINARY, lexer->line, lexer->col};
	}
	if (current == '(' || current == ')' || current == '{' || current == '}' ||
		current == ';' || current == ',')
	{
		char* str = malloc(2);
		str[1] = 0;
		str[0] = current;
		next;
		return (token_t){str, SYMBOL, lexer->line, lexer->col};
	}
	if (current == '.')
	{
		next;

		size_t start = lexer->position;

		while (current >= '0' && current <= '9')
		{
			next;
		}

		size_t length = lexer->position - start;

		char* end_result = malloc(length + 1);
		memset(end_result, 0, length + 1);

		for (size_t i = 0; i < length; ++i)
		{
			end_result[i] = lexer->source[i + start];
		}
		return (token_t){end_result, PIN, lexer->line, lexer->col};
	}
	printf("Unexpeected character '%c' in input.\n", current);
	return (token_t){0};
}

#undef current
