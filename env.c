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
 * write_str - Writes a string to a file descriptor.
 *
 * This function writes the given string to the specified file descriptor.
 *
 * @fd: The file descriptor to write to.
 * @str: The string to be written.
 */
void write_str(int fd, char *str)
{
	write(fd, str, strlen(str));
}

/**
 * print_environment - Prints environment variables to a file descriptor.
 *
 * This function iterates through the environment variables and prints them
 * to the specified file descriptor, one variable per line.
 *
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
 * handle_env_command - Handles the 'env' command.
 *
 * This function forks a child process to print the environment variables
 * to the specified file descriptor using the print_environment function.
 *
 * @fd: The file descriptor to write the output to.
 */
void handle_env_command(int fd)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		write_str(fd, "Fork error\n");
	}
	else if (pid == 0)
	{
		print_environment(fd);
		_exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

int main(void)
{
	char input[BUFFER_SIZE];
	int fd_out = STDOUT_FILENO;
	ssize_t bytes_read;

	while (1)
	{
		write_str(fd_out, "");
		bytes_read = read(STDIN_FILENO, input, sizeof(input));

		if (bytes_read <= 0)
		{
			break;
		}

		input[bytes_read - 1] = '\0';

		if (strcmp(input, "env") == 0)
		{
			handle_env_command(fd_out);
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

	return 0;
}
