#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shead.h"

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t getline_result = 0;
	pid_t pid = -1;
	char **args = NULL;

	handle_input(&input, &input_size);

	while (1)
	{
		handle_prompt();

		handle_getline(&input, &input_size, &getline_result);
		if (execute_command(input))
		{
    		continue;
    	}

		pid = fork();

		if (handle_fork(pid))
		{
			handle_child_or_parent(pid, input);
		}
	}

	handle_cleanup(args, input);
	return (0);
}
