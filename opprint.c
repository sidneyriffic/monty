#include "monty.h"
#include <stdio.h>

void pall(stack_t **top)
{
	stack_t *ptr = *top;

	while (ptr != NULL)
	{
		printf("%d\n", ptr->n);
		ptr = ptr->prev;
	}
}

void pint(stack_t **top)
{
	if (*top == NULL)
		exitwrap(EXIT_FAILURE, "can't pint, stack empty", *top);
	printf("%d\n", (*top)->n);
}

void pchar(stack_t **top)
{
	stack_t *ptr = *top;

	printf("In pchar\n");
	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pchar, stack empty", *top);
	if (ptr->n > 127 || ptr->n < 0)
		exitwrap(EXIT_FAILURE, "can't pchar, value out of range", *top);
	printf("%c\n", ptr->n);
}

void pstr(stack_t **top)
{
	stack_t *ptr = *top;

	if (ptr == NULL)
		printf("\n");
	while (ptr != NULL && !(ptr->n > 127 || ptr->n < 1))
	{
		printf("%c\n", ptr->n);
		ptr = ptr->prev;
	}
}
