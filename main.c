#include "shead.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * main:- main function that control al function
 *
 * Return: o
 */

int main(void)
{
	char *command;
	
	while (1)
	{
		prompt_out();

		command = read_it();

		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		exe_com(command);
		free(command);
	}

	return (0);
}
