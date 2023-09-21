#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * handle_cd - function to handle cd command
 * @args - argument
 * Return: nothing
 */

void handle_cd(char *args[])
{
	if (args[1] == NULL)
	{
		char err_msg[] = "shell: expected argument to \"cd\"\n";
		write(STDERR_FILENO, err_msg, strlen(err_msg));
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			char err_msg[50];
			strcpy(err_msg, "shell: cannot cd into ");
			strcat(err_msg, args[1]);
			strcat(err_msg, "\n");
			write(STDERR_FILENO, err_msg, strlen(err_msg));
		}
	}
}