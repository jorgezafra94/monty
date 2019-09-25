#include "monty.h"

void _push(stack_t **doubly, unsigned int cline)
{
	int n, j;


	for (j = 0; vglo.arg[j] != '\0'; j++)
        {
		if (!isdigit(vglo.arg[j]))
		{
			dprintf(2, "L%u: ", cline);
			dprintf(2, "usage: push integer\n");
			exit(EXIT_FAILURE);
		}
        }
	n = atoi(vglo.arg);

	if (vglo.lifo == 1)
		add_dnodeint(doubly, n);
	else
		add_dnodeint_end(doubly, n);
}

void _pall(stack_t **doubly, unsigned int cline)
{
	stack_t *aux;
	(void)cline;

	aux = *doubly;
	while(aux)
	{
		printf("%d\n",aux->n);
		aux = aux->next;
	}
}

void _pint(stack_t **doubly, unsigned int cline)
{
	(void)cline;

	printf("%d\n", (*doubly)->n);
}

void _pop(stack_t **doubly, unsigned int cline)
{
	stack_t *aux;

	if (doubly == NULL || *doubly == NULL)
	{
		dprintf(2, "L%u: can't pop an empty stack\n", cline);
		exit(EXIT_FAILURE);
	}
	aux = *doubly;
	*doubly = (*doubly)->next;
	free(aux);
}

void _swap(stack_t **doubly, unsigned int cline)
{
	int m = 0;
	stack_t *aux = NULL;

	aux = *doubly;
	for (; aux != NULL; aux = aux->next, m++)
		;
	if (m < 2)
	{
		dprintf(2, "L%u: can't swap, stack too short\n", cline);
		exit(EXIT_FAILURE);
	}
	aux = *doubly;
	*doubly = (*doubly)->next;
	aux->next = (*doubly)->next;
	aux->prev = *doubly;
	(*doubly)->next = aux;
	(*doubly)->prev = NULL;
}
