#include <string.h>
#include "shead.h"
/**
 * execute_command - Executes a command based on the provided input.
 *
 * @input: The command input to be executed.
 * Return: 1 if the input is empty, 0 if it is not.
 */
int execute_command(const char *input)
{
	return (strlen(input) == 0);
}
