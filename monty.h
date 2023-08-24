
#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern int COUNT;
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void popi(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void addi(stack_t **stack, unsigned int line_number);
void nopi(stack_t **stack, unsigned int line_number);
void fres(stack_t *head);
void addnode(stack_t **head, int n);
int execute(char *content, stack_t **stack, FILE *file);
extern FILE *FILEC;
extern char *CONT;
extern instruction_t OPST[] = {
				{"push", push},  
				{"pall", pall},
				{"swap", swap},
				{"add", addi},
				{"nop", nopi},
				{"pint", pint},
				{"pop", popi},
				{NULL, NULL}
				};
extern char *ARG;

#endif