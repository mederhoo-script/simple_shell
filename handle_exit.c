#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * handle_exit - exit
 * @args: args
 */

void handle_exit(char *args[]) 
{
    if (args[1] != NULL) 
	{
        int exit_status = atoi(args[1]);
		if (exit_status > 0)
        	exit(exit_status);
		else if (exit_status < 0)
		{
			perror ("./hsh: 1: exit: Illegal number");
			exit(2);
		}

    }
	else 
	{
        exit(0);
    }
}