#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[2]; /* To store the command and NULL */

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Read user input */
		ssize_t bytes_read = read(STDIN_FILENO, input, sizeof(input));
		if (bytes_read <= 0)
		{
			/* Handle Ctrl+D (end of file) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* Remove the trailing newline character */
		input[bytes_read - 1] = '\0';

		/* Handle the "exit" command */
		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		/* Fork a child process */
		pid_t child_pid = fork();

		if (child_pid < 0)
		{
			char error_message[] = "Fork error\n";
			write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
			_exit(1);
		}
		else if (child_pid == 0)
		{
			/* Child process */

			/* Parse the command */
			args[0] = input;
			args[1] = NULL;

			/* Execute the command */
			execve(args[0], args, NULL);

			/* If execve fails */
			char error_message[] = "Command execution error\n";
			write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
			_exit(1);
		}
		else
		{
			/* Parent process */

			/* Wait for the child process to complete */
			waitpid(child_pid, NULL, 0);
		}
	}

	return 0;
}