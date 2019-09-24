#include "monty.h"

/**
 * gettokens - stores each line of the file input
 *
 * @head: head of the single linked list
 * @buffer: text of the file
 * Return: no return
 */
void gettokens(line_list **head, char *buffer)
{
	line_list *go;
	char *line = NULL;
	char *tokens = NULL;
	char *tokns[2] = {NULL, NULL};

	tokens = _strtoky(buffer, "\n");
	while (tokens)
	{
		add_line_node_end(head, tokens);
		tokens = _strtoky(NULL, "\n");
	}

	go = *head;
	while (go)
	{
		line = _strtoky(go->line, " \t");
		tokns[0] = line;
		if (line)
		{
			printf("%s\n", tokns[0]);
			line = _strtoky(NULL, " \t");
			tokns[1] = line;
		}
		go = go->next;
	}
}

/**
 * _gettext - returns the text of a file
 *
 * @fd: file descriptor
 * Return: a buffer of the text
 */
char *_gettext(int fd)
{
	int num;
	char letter[1] = {0};
	char *li;
	size_t bz;

	num = 0;
	li = NULL;
	bz = 0;

	while ((num = read(fd, letter, 1)) > 0)
	{
		if (bz == 0)
			li = _calloc(bz + 3, sizeof(char));
		else
			li = _realloc(li, bz, bz + 3);
		if (!li)
		{
			num = 0;
			break;
		}
		li[bz] = letter[0], li[bz + 1] = '\n';
		li[bz + 2] = '\0', bz++;
	}

	return (li);
}

/**
 * main - Entry point
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd;
	char *buffer;
	line_list *head = NULL;
/*	stack_t *head = NULL;*/

	if (argc == 1 || argc > 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		dprintf(2, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	buffer = _gettext(fd);
	gettokens(&head, buffer);

	free(buffer);
	free_line_list(&head);

	return (0);
}
