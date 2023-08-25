#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shead.h"

/**
 * read_it - function to read input
 *
 * Return: void
 */

char *read_it(void)
{
	int buf_size = 256;
	int i = 0;
	char *buffer = malloc(buf_size * sizeof(char));

	if (!buffer)
	{
		perror("malloc fail");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		char c;
		int result;

		result = read(STDIN_FILENO, &c, 1);

		if (result == -1)
		{
			perror("read fail");
			exit(EXIT_FAILURE);
		}
/*reset \n to '\0' */
		if (result == 0 || c == '\n')
		{
			buffer[i] = '\0';
			return (buffer);
		}
		else
		{
			buffer[i] = c;
		}

		i++;
	}
}
