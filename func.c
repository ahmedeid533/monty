#include "monty.h"
/**
 * addnode - add node to the head stack
 * @head: head of the stack
 * @n: new_value
 * Return: no return
*/
void addnode(stack_t **head, int n)
{

	stack_t *new_node, *aux;

	aux = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		printf("Error\n");
		exit(0); 
	}
	if (aux)
		aux->prev = new_node;
	new_node->n = n;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}
/**
* execute - executes the opcode
* @stack: head linked list - stack
* @file: poiner to monty file
* @content: line content
* Return: no return
*/
int execute(char *content, stack_t **stack, FILE *file)
{
	unsigned int i;
	char *op;

    op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	ARG = strtok(NULL, " \n\t");
	while (OPST[i].opcode && op)
	{
		if (strcmp(op, OPST[i].opcode) == 0)
		{	OPST[i].f(stack, COUNT);
			return (0);
		}
		i++;
	}
	if (op && OPST[i].opcode == NULL)
	{ 
		fprintf(stderr, "L%d: unknown instruction %s\n", COUNT, op);
		fclose(file);
		free(content);
		fres(*stack);
		exit(EXIT_FAILURE); 
	}
	return (1);
}
/**
 * f_push - add node to the stack
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void push(stack_t **head, unsigned int counter)
{
	int n, j = 0, flag = 0;

	if (ARG)
	{
		if (ARG[0] == '-')
			j++;
		for (; ARG[j] != '\0'; j++)
		{
			if (ARG[j] > 57 || ARG[j] < 48)
				flag = 1; 
		}
		if (flag == 1)
		{
			fprintf(stderr, "L%d: usage: push integer\n", counter);
			fclose(FILEC);
			free(CONT);
			fres(*head);
			exit(EXIT_FAILURE);
			}
	}
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", counter);
		fclose(FILEC);
		free(CONT);
		fres(*head);
		exit(EXIT_FAILURE); 
	}
	n = atoi(ARG);
	addnode(head, n);
}

/**
 * f_pall - prints the stack
 * @head: stack head
 * @counter: no used
 * Return: no return
*/
void pall(stack_t **head, unsigned int counter)
{
	stack_t *h;
	(void)counter;

	h = *head;
	if (h == NULL)
		return;
	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
}

/**
 * f_pop - prints the top
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void popi(stack_t **head, unsigned int counter)
{
	stack_t *h;

	if (*head == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", counter);
		fclose(FILEC);
		free(CONT);
		fres(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	*head = h->next;
	free(h);
}