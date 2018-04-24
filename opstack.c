#include "monty.h"

void push(stack_t **top, stack_t **bot, int val, int mode)
{
	stack_t *ptr;

	ptr = malloc(sizeof(stack_t));
	if (ptr == NULL)
	{
		/* print malloc fail and exit */
		exit(-1);
	}
	ptr->n = val;
	if (*top == NULL)
	{
		ptr->prev = NULL;
		ptr->next = NULL;
		*top = ptr;
		*bot = ptr;
	}
	else if (mode == STACKMODE)
	{
		ptr->next = NULL;
		ptr->prev = *top;
		(*top)->next = ptr;
		*top = ptr;
	}
	else if (mode == QUEUEMODE)
	{
		ptr->prev = NULL;
		ptr->next = *bot;
		(*bot)->prev = ptr;
		*bot = ptr;
	}
}

void pop(stack_t **top)
{
	stack_t *ptr = *top;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
	{
		free(*top);
		*top = NULL;
	}
	else
	{
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
	}
}

void swap(stack_t **top, stack_t **bot)
{
	stack_t *ptr = *top;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't swap, stack too short");
	ptr = ptr->prev;
	(*top)->prev = ptr->prev;
	ptr->next = (*top)->next;
	ptr->prev = *top;
	(*top)->next = ptr;
	if ((*bot)->prev != NULL)
		*bot = (*bot)->prev;
}
