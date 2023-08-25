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
int execute(char *content, stack_t **stack, FILE *file, unsigned int count)
{
	instruction_t opst[] = {
				{"push", push},
				{"pall", pall},
				{"pint", pint},
				{"pop", popi},
				{"swap", swap},
				{"add", addi},
				{"nop", nopi},
				{NULL, NULL}
				};
	unsigned int i = 0;
	char *op;

	op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	GOLV.ARG = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{	
			opst[i].f(stack, count);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", count, op);
		fclose(file);
		free(content);
		fres(*stack);
		exit(EXIT_FAILURE);
	}
	return (1);
}
/**
 * push - add node to the stack
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void push(stack_t **head, unsigned int counter)
{
	int n, j = 0, flag = 0;

	if (GOLV.ARG)
	{
		if (GOLV.ARG[0] == '-')
			j++;
		for (; GOLV.ARG[j] != '\0'; j++)
		{
			if (GOLV.ARG[j] > 57 || GOLV.ARG[j] < 48)
				flag = 1;
		}
		if (flag == 1)
		{
			fprintf(stderr, "L%d: usage: push integer\n", counter);
			fclose(GOLV.FILEC);
			free(GOLV.CONT);
			fres(*head);
			exit(EXIT_FAILURE);
			}
	}
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", counter);
		fclose(GOLV.FILEC);
		free(GOLV.CONT);
		fres(*head);
		exit(EXIT_FAILURE);
	}
	n = atoi(GOLV.ARG);
	addnode(head, n);
}

/**
 * pall - prints the stack
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
 * popi - prints the top
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
		fclose(GOLV.FILEC);
		free(GOLV.CONT);
		fres(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	*head = h->next;
	free(h);
}
