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
        exit(exit_status);
    } 
	else 
	{
        exit(0);
    }
}