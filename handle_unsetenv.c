#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * handle_unsetenv - 
 * @args: args pass
 */

void handle_unsetenv(char *args[]) 
{
    if (args[1] == NULL || args[2] != NULL) 
	{
        char err_msg[] = "Usage: unsetenv VARIABLE\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));
    } 
	else 
	{
        if (unsetenv(args[1]) != 0) 
		{
            char err_msg[50];
            strcpy(err_msg, "shell: cannot unset environment variable ");
            strcat(err_msg, args[1]);
            strcat(err_msg, "\n");
            write(STDERR_FILENO, err_msg, strlen(err_msg));
        }
    }
}