#include "monty.h"

GOL GOLV = {NULL, NULL, NULL};
struct instruction_s OPST[8];
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
	unsigned int count = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	GOLV.FILEC = file;
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		content = NULL;
		read_line = getline(&content, &size, file);
		count++;
		if (read_line > 0)
		{
			execute(content, &stack, file, count);
		}
		free(content);
	}
	fres(stack);
	fclose(file);
	return (0);
}

/**
* fres - frees a doubly linked list
* @head: head of the stack
*/
void fres(stack_t *head)
{
	stack_t *aux;

	aux = head;
	while (head)
	{
		aux = head->next;
		free(head);
		head = aux;
	}
}

/**
 * swap - adds the top two elements of the stack.
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void swap(stack_t **head, unsigned int counter)
{
	stack_t *h;
	int len = 0, aux;

	h = *head;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", counter);
		fclose(GOLV.FILEC);
		free(GOLV.CONT);
		fres(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	aux = h->n;
	h->n = h->next->n;
	h->next->n = aux;
}
/**
  *nopi - nothing
  *@head: stack head
  *@counter: line_number
  *Return: no return
 */
void nopi(stack_t **head, unsigned int counter)
{
	(void) counter;
	(void) head;
}
