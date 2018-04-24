#include "monty.h"

#include <stdio.h>

void add(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't add, stack too short");
	else
	{
		num = ptr->n;
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n += num;
	}
}

void sub(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't sub, stack too short");
	else
	{
		num = ptr->n;
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n -= num;
	}
}

void mul(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't mul, stack too short");
	else
	{
		num = ptr->n;
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n *= num;
	}
}

void _div(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't div, stack too short");
	else
	{
		num = ptr->n;
		if (num == 0)
			exitwrap(EXIT_FAILURE, "division by zero");
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n /= num;
	}
}

void mod(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack");
	if (ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't mod, stack too short");
	else
	{
		num = ptr->n;
		if (num == 0)
			exitwrap(EXIT_FAILURE, "division by zero");
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n %= num;
	}
}
