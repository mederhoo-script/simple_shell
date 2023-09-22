#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * handle_setenv - setenv
 * @args: args
 */

void handle_setenv(char *args[]) 
{
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL) 
	{
        char err_msg[] = "Usage: setenv VARIABLE VALUE\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));
    } 
	else 
	{
        if (setenv(args[1], args[2], 1) != 0) 
		{
            char err_msg[50];
            strcpy(err_msg, "shell: cannot set environment variable ");
            strcat(err_msg, args[1]);
            strcat(err_msg, "\n");
            write(STDERR_FILENO, err_msg, strlen(err_msg));
        }
    }
}