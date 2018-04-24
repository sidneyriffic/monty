#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>
#include <string.h>

#define MONTYOPCT 14

/* should free stack here */
void exitwrap(int exitcode)
{
	exit(exitcode);
}

/* note that bot is updated to NULL only in the case of pushing with
 * NULL top. All other opcodes using bot should check if top is NULL
 * first. */
int montyparse(FILE *script, optype *ops)
{
	int val, mode = STACKMODE;
	size_t len = 0;
	ssize_t linenum = 1;
	stack_t *top = NULL, *bot = NULL;
	char *buffer = NULL, *tok;

	while (getline(&buffer, &len, script) > 0)
	{
		tok = strtok(buffer, " \n");
		if (tok == NULL)
			return (0);
		val = 0;
		if (*tok == '#' || !strcmp(tok, "nop"))
			;
		else if (!strcmp(tok, "queue"))
			mode = QUEUEMODE;
		else if (!strcmp(tok, "queue"))
			mode = STACKMODE;
		else
		{
			while (!strcmp(tok, ops[val].opcode) && val < MONTYOPCT)
				val++;
			if (val == MONTYOPCT)
				return (-2);
			if (val == 0)
			{
				tok = strtok(NULL, " \n");
				if (tok == NULL)
					return (-4);
				if (top == NULL)
					bot = NULL;
				ops[0].func.pushmode(&top, &bot, val, mode);
				if (bot == NULL)
					bot = top;
			}
			if (val < 4)
				ops[val].func.topbot(&top, &bot);
			if (val < MONTYOPCT)
				ops[val].func.toponly(&top);
			return (-1);
		}
		linenum++;
	}
	return (0);
}

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

int main(int ac, char *av[])
{
	FILE *script;
	int ret;
	optype *ops;

	if (ac != 2)
	{
		printf("USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	script = fopen(av[1], "r");
	if (script == NULL)
	{
		printf("Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	ops = initops();
	ret = montyparse(script, ops);
	fclose(script);
	return (0);
}

#undef MONTYOPCT
