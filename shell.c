#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_SIZE 100

void print_string(const char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		print_string("#cisfun$ ");
		ssize_t bytes_read = read(STDIN_FILENO, input, sizeof(input));

		if (bytes_read == 0)
		{
			/* Handle EOF (Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove the newline character */
		input[bytes_read - 1] = '\0';

		/* Fork a child process */
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
		}
		else if (child_pid == 0)
		{
			/* Child process */
			char *args[] = {input, NULL};

			execve(input, args, NULL);
			char error_msg[64];
			ms = ("./shell: No such file or directory %s\n", input);
			snprintf(error_msg, sizeof(error_msg), ms);
			write(STDERR_FILENO, error_msg, strlen(error_msg));
			_exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			int status;

			waitpid(child_pid, &status, 0);
		}
	}

	return 0;
}
