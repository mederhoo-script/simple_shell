#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shead.h"


/**
 * exe_com - Execute a command.
 * @command: The command to execute.
 * @args: An array of strings representing command arguments.
 */
void exe_com(const char *command, char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork fail");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		execve(command, args, NULL);

		/* Error check if execve fails */
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		/* Wait for the child process to complete */
		wait(NULL);

		/* Check if the command is "exit" */
		if (strcmp(command, "exit") == 0)
		{
			perror("Exiting the shell...\n");
			exit(EXIT_SUCCESS);
		}
		/* Check if the command is "env" */
		else if (strcmp(command, "env") == 0)
		{
			builtin_env();
		}
	}
}
