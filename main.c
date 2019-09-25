#include "monty.h"
global_t vglo;

void start_vglo(void)
{
	vglo.lifo = 1;
	vglo.cont = 1;
	vglo.arg = NULL;
	vglo.head = NULL;
}

FILE *check_input(int argc, char *argv[])
{
	FILE *fd;
	if (argc == 1 || argc > 2)
        {
                dprintf(2, "USAGE: monty file\n");
                exit(EXIT_FAILURE);
        }
        fd = fopen(argv[1], "r");
        if (fd == NULL)
        {
                dprintf(2, "Error: Can't open file %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }
	return (fd);
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
	void (*f)(stack_t **stack, unsigned int line_number);
	FILE *fd;
	size_t size = 256;
	ssize_t nlines = 0;
	char *buffer = NULL,  *lines[2] = {NULL, NULL};

	fd = check_input(argc, argv);
	start_vglo();
	nlines = getline(&buffer, &size, fd);
	while (nlines != -1)
	{
		lines[0] = _strtoky(buffer, " \t\n");
		if (lines[0])
		{
			f = get_opcodes(lines[0]);
			if (!f)
			{
				dprintf(2, "L%u: ", vglo.cont);
				dprintf(2, "unknown instruction %s\n", lines[0]);
				exit(EXIT_FAILURE);
			}
			vglo.arg = _strtoky(NULL, " \t\n");
			f(&vglo.head, vglo.cont);
		}
		nlines = getline(&buffer, &size, fd);
		vglo.cont++;
	}
	return (0);
}
