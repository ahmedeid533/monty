#include "monty.h"

/**
* main - monty code interpreter
* @argc: number of arguments
* @argv: monty file location
* Return: 0 on success
*/
int main(int argc, char *argv[])
{
	char *content;
	FILE *file;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;

	def();
	COUNT = 0;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		content = NULL;
		read_line = getline(&content, &size, file);
		COUNT++;
		if (read_line > 0)
		{
			execute(content, &stack, file);
		}
		free(content);
	}
	fres(stack);
	fclose(file);
	return (0);
}
/**
 * def - def
 * 
 */
void def()
{
	OPST[0].opcode = "push";
	OPST[0].f = push;
	OPST[1].opcode = "pall";
	OPST[1].f = pall;
	OPST[2].opcode = "swap";
	OPST[2].f = swap;
	OPST[3].opcode = "add";
	OPST[3].f = addi;
	OPST[4].opcode = "nop";
	OPST[4].f = nopi;
	OPST[5].opcode = "pint";
	OPST[5].f = pint;
	OPST[6].opcode = "pop";
	OPST[6].f = popi;
	OPST[7].opcode = NULL;
	OPST[6].f = NULL;
}