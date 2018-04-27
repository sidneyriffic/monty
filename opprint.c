#include "monty.h"
#include <stdio.h>

/**
 * pall - print all values as integers
 *
 * @top: top of stack
 */
void pall(stack_t **top)
{
	stack_t *ptr = *top;

	while (ptr != NULL)
	{
		printf("%d\n", ptr->n);
		ptr = ptr->prev;
	}
}

/**
 * pint - print top of stack as an integer
 *
 * @top: top of stack
 */
void pint(stack_t **top)
{
	if (*top == NULL)
		exitwrap(EXIT_FAILURE, "can't pint, stack empty", *top);
	printf("%d\n", (*top)->n);
}

/**
 * pchar - print top of stack as a char
 *
 * @top: top of stack
 */
void pchar(stack_t **top)
{
	stack_t *ptr = *top;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pchar, stack empty", *top);
	if (ptr->n > 127 || ptr->n < 0)
		exitwrap(EXIT_FAILURE, "can't pchar, value out of range", *top);
	printf("%c\n", ptr->n);
}

/**
 * pstr - print stack as string starting from the top
 * stop on 0 or out of ascii bounds
 *
 * @top: top of stack
 */
void pstr(stack_t **top)
{
	stack_t *ptr = *top;

	while (ptr != NULL && ptr->n <= 127 && ptr->n > 0)
	{
		printf("%c", ptr->n);
		ptr = ptr->prev;
	}
	printf("\n");
}
