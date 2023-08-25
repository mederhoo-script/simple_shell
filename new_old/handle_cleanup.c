#include <stdio.h>
#include <stdlib.h>
#include "shead.h"
#include <string.h>


/**
 * handle_cleanup - Frees memory allocated for arguments and input.
 * * * @args: Pointer to the array of command arguments (can be NULL).
 * @input: Pointer to dynamically allocated).
 */
void handle_cleanup(char **args, char *input)
{
	if (args != NULL)
	{
		free(args);
	}
	free(input);
}

/**
 * handle_empty_input - Checks if the provided input is empty.
 *
 * @input: The input string to be checked.
 * Return: 1 if the input is empty, 0 if it's not.
 */
int handle_empty_input(const char *input)
{
	return (strlen(input) == 0);
}

/**
 * handle_input - Handles input reading from non-interactive streams.
 * @input: Pointer to a buffer to store the input line.
 * @input_size: Pointer to the size of the input buffer.
 */
void handle_input(char **input, size_t *input_size)
{
	if (!isatty(STDIN_FILENO))
	{
		getline(input, input_size, stdin);
		(*input)[strcspn(*input, "\n")] = '\0';
	}
}
