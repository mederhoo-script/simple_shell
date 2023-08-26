#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_ENV_VARS 100
#define BUFFER_SIZE 1024

extern char **environ;

/**
 * write_str - Write a string to a file descriptor.
 * @fd: The file descriptor to write to.
 * @str: The string to write.
 */
void write_str(int fd, char *str)
{
	write(fd, str, strlen(str));
}

/**
 * print_environment - Print the environment variables.
 * @fd: The file descriptor to write to.
 */
void print_environment(int fd)
{
	char **env = environ;
	while (*env != NULL)
	{
		write_str(fd, *env);
		write_str(fd, "\n");
		env++;
	}
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[BUFFER_SIZE];
	int fd_out = STDOUT_FILENO;
	ssize_t bytes_read;

	while (1)
	{
		write_str(fd_out, "$ ");
		bytes_read = read(STDIN_FILENO, input, sizeof(input));

		if (bytes_read <= 0)
		{
			break;
		}

		input[bytes_read - 1] = '\0'; /* Remove newline character */

		if (strcmp(input, "env") == 0)
		{
			pid_t pid = fork();
			if (pid < 0)
			{
				/* Handle fork error */
			}
			else if (pid == 0)
			{
				/* Child process */
				print_environment(fd_out);
				_exit(0);
			}
			else
			{
				/* Parent process */
				waitpid(pid, NULL, 0);
			}
		}
		else if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else
		{
			write_str(fd_out, "Command not found\n");
		}
	}

	return (0);
}
