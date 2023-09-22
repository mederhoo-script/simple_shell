#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * special_variable - spec char
 * @var: variable
 * Return:NULL
 */

char *special_variable(char *var) 
{
	int i;
    if (strcmp(var, "$$") == 0) 
	{
        char *pid_str = malloc(16);
        int pid = getpid();
        int len = 0;
        while (pid > 0) 
		{
            pid_str[len++] = '0' + (pid % 10);
            pid /= 10;
        }
        pid_str[len] = '\0';
        /* Reverse the string */
        for (i = 0; i < len / 2; i++) 
		{
            char temp = pid_str[i];
            pid_str[i] = pid_str[len - i - 1];
            pid_str[len - i - 1] = temp;
        }
        return pid_str;
    } 
	else if (strcmp(var, "$?") == 0) 
	{
        return "NotImplemented";
    } 	
	else if (strcmp(var, "$PATH") == 0) 
	{
        char *path = getenv("PATH");
        if (path == NULL)
		{
            return "PATH not set";
        } else
		{
            return path;
        }
    } 
	else 
	{
        return NULL;
    }
}