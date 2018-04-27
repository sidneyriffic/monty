#include "monty.h"

#include <stdio.h>

/**
 * add - add top two stack elements. error if < 2 elements
 *
 * @top: top of stack
 */
void add(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't add, stack too short", *top);
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

/**
 * sub - subtract top two stack elements. error if < 2 elements
 *
 * @top: top of stack
 */
void sub(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't sub, stack too short", *top);
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

/**
 * mul - multiply top two stack elements. error if < 2 elements
 *
 * @top: top of stack
 */
void mul(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't mul, stack too short", *top);
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

/**
 * _div - divide top two stack elements. error if < 2 elements or divby0
 *
 * @top: top of stack
 */
void _div(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't div, stack too short", *top);
	else
	{
		num = ptr->n;
		if (num == 0)
			exitwrap(EXIT_FAILURE, "division by zero", *top);
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n /= num;
	}
}

/**
 * mod - get remainder top two stack elements. error if < 2 elements or divby0
 *
 * @top: top of stack
 */
void mod(stack_t **top)
{
	stack_t *ptr = *top;
	long num;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't mod, stack too short", *top);
	else
	{
		num = ptr->n;
		if (num == 0)
			exitwrap(EXIT_FAILURE, "division by zero", *top);
		ptr = ptr->prev;
		ptr->next = NULL;
		free(*top);
		*top = ptr;
		ptr->n %= num;
	}
}
