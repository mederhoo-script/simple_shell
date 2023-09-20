#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * execute_command - to handle command
 * @args:
 * Return nothing
 */

void execute_command(char *args[])
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			char err_msg[50];

			strcpy(err_msg, "shell: command not found: ");
			strcat(err_msg, args[0]);
			strcat(err_msg, "\n");
			write(STDERR_FILENO, err_msg, strlen(err_msg));
			_exit(EXIT_FAILURE);
		}
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		/* Parent process */
		do

		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}

		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
