#ifndef MONTYH
#define MONTYH

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcoode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* montyparse.c */
instruction_t *initopcodes();

/* opstack.c */
int push(stack_t **top, int mode);
int pop(stack_t **top);
int swap(stack_t **top);
void rotl(stack_t **top, stack_t **bot);
void rotr(stack_t **top, stack_t **bot);

/* opprint.c */
void pall(stack_t *top);
int pint(stack_t *top);
int pchar(stack_t *top);
void pstr(stack_t *top);

/* opmath.c */
int add(stack_t **top);
int sub(stack_t **top);
int mul(stack_t **top);
int div(stack_t **top);
int mod(stack_t **top);


#endif
