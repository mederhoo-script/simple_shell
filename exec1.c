#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shead.h"

/**
 * exe_com - function that execute command
 * @command: - parameter to be execute
 */

void exe_com(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork fail");
		exit(EXIT_FAILURE);
	}
	/*0 is child pid */
	else if (pid == 0)
	{
		/*Child process */
		const char *args[2];

		args[0] = command;
		args[1] = NULL;

		execve(command, (char *const *)args, NULL);

		/*error check If execve fails*/
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		/**
		 * Parent proces
		 * Wait for the child process to complete
		 */
		wait(NULL);
	}
}
