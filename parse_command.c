#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"


int parse_command(char *input, char *args[]) 
{
    int i = 0;
    char *token = strtok(input, " \n;");

    while (token != NULL) 
	{
        args[i++] = token;
        token = strtok(NULL, " \n;");
    }
    args[i] = NULL;

    return i;
}