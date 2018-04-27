#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>
#include <string.h>

#define MONTYOPCT 14

static montyglob mglob;

/**
 * exitwrap - free things and exit the program. Print error message as needed
 *
 * @exitcode: exit code
 * @exitstring: error string to print, if any
 * @top: top of stack (for freeing)
 */
void exitwrap(int exitcode, char *exitstring, stack_t *top)
{
	stack_t *ptr = top;

	if (exitstring != NULL)
		printf("L%lu: %s\n", mglob.linenum, exitstring);
	while (top != NULL)
	{
		ptr = top->prev;
		free(top);
		top = ptr;
	}
	free(mglob.buffer);
	fclose(mglob.script);
	exit(exitcode);
}

/**
 * isnumstr - checks if a string is a number
 *
 * @str: string to check
 *
 * Return: 1 if numeric, 0 otherwise
 */
int isnumstr(char *str)
{
	if (*str == '-')
	{
		str++;
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	while (*str != 0)
		if (*str < '0' || *str++ > '9')
			return (0);
	return (1);
}

/**
 * montyparse - parser for monty script files
 * note that bot is updated to NULL only in the case of pushing with
 * NULL top. All other opcodes using bot should check if top is NULL
 * first.
 *
 * @ops: array of opcodes and pointers to functions for them
 *
 * Return: 0 if successful
 */
int montyparse(optype *ops)
{
	size_t len = 0, val, mode = STACKMODE;
	stack_t *top = NULL, *bot = NULL;
	char *tok;

	while (getline(&mglob.buffer, &len, mglob.script) > 0)
	{
		if (mglob.buffer == NULL)
		{
			printf("Error: malloc failed\n");
			exitwrap(EXIT_FAILURE, NULL, top);
		}
		tok = strtok(mglob.buffer, "\n ");
		if (tok != NULL)
		{
			val = 0;
			if (*tok == '#' || !strcmp(tok, "nop"))
				;
			else if (!strcmp(tok, "queue"))
				mode = QUEUEMODE;
			else if (!strcmp(tok, "stack"))
				mode = STACKMODE;
			else
			{
				while (val < MONTYOPCT && strcmp(tok, ops[val].opcode))
					val++;
				if (val == 0)
				{
					tok = strtok(NULL, "\n ");
					if (tok == NULL || !isnumstr(tok))
						exitwrap(EXIT_FAILURE, "usage: push integer", top);
					ops[0].func.pushmode(&top, &bot, atoi(tok), mode);
				}
				else if (val < 4)
					ops[val].func.topbot(&top, &bot);
				else if (val < MONTYOPCT)
					ops[val].func.toponly(&top);
				else
				{
					printf("L%ld: unknown instruction %s\n", mglob.linenum, tok);
					exitwrap(EXIT_FAILURE, NULL, top);
				}
			}
		}
		free(mglob.buffer);
		mglob.buffer = NULL;
		len = 0;
		mglob.linenum++;
	}
	exitwrap(EXIT_SUCCESS, NULL, top);
	return (0);
}

/**
 * initops - initialize array of opcodes and functions for them
 *
 * Return: array of optypes
 */
optype *initops()
{
	static optype head[14];

	head[0].opcode = "push";
	head[0].func.pushmode = push;
	head[1].opcode = "rotl";
	head[1].func.topbot = rotl;
	head[2].opcode = "rotr";
	head[2].func.topbot = rotr;
	head[3].opcode = "swap";
	head[3].func.topbot = swap;
	head[4].opcode = "pop";
	head[4].func.toponly = pop;
	head[5].opcode = "pall";
	head[5].func.toponly = pall;
	head[6].opcode = "pint";
	head[6].func.toponly = pint;
	head[7].opcode = "pchar";
	head[7].func.toponly = pchar;
	head[8].opcode = "pstr";
	head[8].func.toponly = pstr;
	head[9].opcode = "add";
	head[9].func.toponly = add;
	head[10].opcode = "sub";
	head[10].func.toponly = sub;
	head[11].opcode = "mul";
	head[11].func.toponly = mul;
	head[12].opcode = "div";
	head[12].func.toponly = _div;
	head[13].opcode = "mod";
	head[13].func.toponly = mod;

	return (head);
}

/**
 * main - parse a monty script file
 *
 * @ac: number of arguments
 * @av: argument array
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int main(int ac, char *av[])
{
	optype *ops;

	if (ac != 2)
	{
		printf("USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	mglob.script = fopen(av[1], "r");
	if (mglob.script == NULL)
	{
		printf("Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	ops = initops();
	mglob.linenum = 1;
	montyparse(ops);
	return (0);
}

#undef MONTYOPCT
