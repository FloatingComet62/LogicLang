#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char bool;
#define true 1
#define false 0

#define panic(str) printf("PANIC: %s\n", str)

char* help_message = "~~ USAGE ~~\n\n exec [INPUT FILE]\n";
char** argv;
int argc;
char* shift()
{
	char* str = *argv;
	++argv;
	--argc;
	return str;
}

char* get_input_file()
{
	if (!argc)
	{
		printf("No args provided.\n%s\n", help_message);
		exit(1);
	}
	while (argc)
	{
		char* next = shift();
		if (next[0] != '-')
		{
			return next;
		}
	}
}

char* read_file(char* fp)
{
	FILE* f = fopen(fp, "r");

	if (!f)
	{
		// not a real faliure more of a mistake.
		printf("File '%s' does not exist.", fp);
		exit(0);
	}

	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* string = malloc(fsize + 1);
	memset(string, 0, fsize + 1);

	bool success = fread(string, fsize, 1, f);
	if (!success)
	{
		panic("Could not read file.");
	}

	fclose(f);

	return string;
}

int main(int x, char** y)
{
	// Use X and Y as args because argv and argc are global.
	argv = y;
	argc = x;

	char* exec_path = shift();	// this is the file name of the executable.

	char* in_file = get_input_file();

	char* src = read_file(in_file);
	printf("~~ SOURCE ~~\n%s\n~~ END OF SOURCE ~~\n", src);
}
