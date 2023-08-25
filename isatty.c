#include <unistd.h>
#include "shead.h"

/**
 * is_pipe_input - Checks if the program's
 * Return: 1 if input is from a pipe or file, 0 if inpu
*/
int is_pipe_input(void)
{
	return (!isatty(STDIN_FILENO));
}
