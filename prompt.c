#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shead.h"

/**
 * prompt_out - prompt to the terminal
 *
 * return: void
 */

void prompt_out(void)
{
	if (isatty(STDIN_FILENO))
	{
	char *prompt = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, strlen(prompt));

	}
}
