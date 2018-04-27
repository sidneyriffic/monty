#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>

/**
 * push - pushes a value onto the stack and updates pointers
 *
 * @top: top of stack
 * @bot: bottom of stack
 * @val: value to push
 * @mode: stack or queue mode (put on top or bottom)
 */
void push(stack_t **top, stack_t **bot, int val, int mode)
{
	stack_t *ptr;

	ptr = malloc(sizeof(stack_t));
	if (ptr == NULL)
	{
		printf("Error: malloc failed\n");
		exitwrap(EXIT_FAILURE, NULL, *top);
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

/**
 * pop - pop top element of stack
 *
 * @top: top of stack
 */
void pop(stack_t **top)
{
	stack_t *ptr = *top;

	if (ptr == NULL)
		exitwrap(EXIT_FAILURE, "can't pop an empty stack", *top);
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

/**
 * swap - swap top two values on stack and update top/bottom
 *
 * @top: top of stack
 * @bot: bottom of stack
 */
void swap(stack_t **top, stack_t **bot)
{
	stack_t *ptr = *top;

	if (ptr == NULL || ptr->prev == NULL)
		exitwrap(EXIT_FAILURE, "can't swap, stack too short", *top);
	ptr = ptr->prev;
	(*top)->prev = ptr->prev;
	ptr->next = (*top)->next;
	ptr->prev = *top;
	(*top)->next = ptr;
	*top = ptr;
	if ((*bot)->prev != NULL)
		*bot = (*bot)->prev;
}

/**
 * rotl - "rotate left" put top of stack on bottom
 *
 * @top: top of stack
 * @bot: bottom of stack
 */
void rotl(stack_t **top, stack_t **bot)
{
	stack_t *ptrt = *top, *ptrb = *bot;

	if (ptrt == NULL || ptrt->prev == NULL)
		return;
	ptrt->next = ptrb;
	ptrb->prev = ptrt;
	*top = ptrt->prev;
	(*top)->next = NULL;
	*bot = ptrt;
	ptrt->prev = NULL;
}

/**
 * rotr - "rotate right" put bottom of stack on top
 *
 * @top: top of stack
 * @bot: bottom of stack
 */
void rotr(stack_t **top, stack_t **bot)
{
	stack_t *ptrt = *top, *ptrb = *bot;

	if (ptrt == NULL || ptrt->prev == NULL)
		return;
	ptrt->next = ptrb;
	ptrb->prev = ptrt;
	*bot = ptrb->next;
	(*bot)->prev = NULL;
	*top = ptrb;
	ptrb->next = NULL;
}
