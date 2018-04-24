#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>
#include <string.h>

int montyparse(FILE *script, optype *ops)
{
	int val;
	size_t len = 0;
	ssize_t glret, linenum = 0;
	stack_t *bot = NULL, *top = NULL;
	char *buffer = NULL, *tok;

	while ((glret = getline(&buffer, &len, script)) > 0)
	{
		tok = strtok(buffer, " \n");
		if (tok == NULL)
			return (-2);
	}
	if (glret == -1)
		return (-1);
}

optype *initops()
{
	static optype head[14];

	head[0].opcode = "push";
	head[0].func.pushmode = push;
	head[1].opcode = "pop";
	head[1].func.toponly = pop;
	head[2].opcode = "swap";
	head[2].func.toponly = swap;
	head[3].opcode = "rotl";
	head[3].func.topbot = rotl;
	head[4].opcode = "rotr";
	head[4].func.topbot = rotr;
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
	head[12].func.toponly = div;
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
	if (ret == -1)
	{
		printf("Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	return (0);
}
