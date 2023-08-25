#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shead.h"

/**
 * handle_prompt - Handles printing a prompt to the user.
 *
 * This function displays a prompt to the user if the standard input is
 * connected to an interactive terminal. It prints the defined 'PROMPT'
 * string to the standard output.
 */
void handle_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

/**
 * handle_getline - Handles reading a line of input from the user.
 *
 * This function reads a line of input from the user if the standard input
 * end-of-file (EOF) condition is encountered, the function handles it.
 *
 * @input: Pointer to a buffer to store the input
 * @input_size: Pointer to the size of the input buffer.
 * @getline_result: Pointer to store the result of the 'getline' function.
 */
void handle_getline(char **input, size_t *input_size, ssize_t *getline_result)
{
	if (isatty(STDIN_FILENO))
	{
		*getline_result = getline(input, input_size, stdin);

		if (*getline_result == -1)
		{
			handle_eof(*getline_result);
		}

		(*input)[strcspn(*input, "\n")] = '\0';
	}
}
