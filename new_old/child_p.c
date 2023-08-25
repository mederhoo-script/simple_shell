#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shead.h"


#define PROMPT "#cisfun$ "
#define MAX_INPUT_SIZE 256
#define MAX_PATH_SIZE 256

/**
 * handle_child_process - Executes a child process.
 *
 * @input: The command input to be executed.
 */
void handle_child_process(const char *input)
{
	char path[MAX_PATH_SIZE];
	char **args;

	args = (char **)malloc(sizeof(char *) * 2);
	args[0] = strdup(input);
	args[1] = NULL;

	handle_construct_path(path, input);

	execve(path, args, NULL);

	perror("execve");
	exit(EXIT_FAILURE);
}
