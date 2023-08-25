#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_INPUT_SIZE 256
#define MAX_PATH_SIZE 256

/**
 * readInput - Reads input from standard input.
 *
 * This function uses the 'getline' function to read input from the user
 * via standard input. If an end-of-file condition is encountered, the
 * program is terminated. The newline character is removed from the input.
 *
 * @input: Pointer to a buffer to store the input line.
 * @input_size: Pointer to the size of the input buffer.
 */
void readInput(char **input, size_t *input_size)
{
	ssize_t getline_result = getline(input, input_size, stdin);

	if (getline_result == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		} else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	(*input)[strcspn(*input, "\n")] = '\0';
}

/**
 * parseInput - Parses input into argument array.
 *
 * This function takes an input string and creates an argument array
 * for use with the 'execve' function. It allocates memory for the array
 * and sets up the arguments. The array must be freed after use.
 *
 * @input: The input string to be parsed.
 * Return: A pointer to the argument array.
 */
char **parseInput(char *input)
{
	char **args = (char **)malloc(sizeof(char *) * 2);

	args[0] = input;
	args[1] = NULL;
	return (args);
}

/**
 * executeCommand - Executes a command.
 *
 * This function creates a child process using 'fork' and executes
 * the provided command input using 'execve'. The parent process waits
 * for the child process to complete. Errors during execution are handled.
 *
 * @input: The command input to be executed.
 */
void executeCommand(char *input)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		/* Child process */
		char path[MAX_PATH_SIZE];
		char **args;

		if (input[0] == '/')
		{
			/* Input starts with '/', use input directly as the path */
			strcpy(path, input);
		}
		else
		{
			/* Construct path by adding '/bin/' to the input */
			strcpy(path, "/bin/");
			strcat(path, input);
		}

		args = parseInput(input);

		execve(path, args, NULL);

		/* If execve returns, there was an error */
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 * main - Entry point of the program.
 *
 * This function reads and executes commands from the user input
 * or from a non-interactive input source (like a pipe or file).
 * It provides a prompt for interactive input and handles command execution.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	/* Check if there's input from a pipe */
	if (!isatty(STDIN_FILENO))
	{
		readInput(&input, &input_size);
		input[strcspn(input, "\n")] = '\0';
		executeCommand(input);
		free(input);
		return (0);
	}

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		readInput(&input, &input_size);

		if (strlen(input) == 0)
		{
			continue; /* Empty input, show prompt again */
		}

		executeCommand(input);

		free(input);
	}

	return (0);
}
