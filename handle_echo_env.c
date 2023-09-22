#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * handle_echo_env -handle echo
 * @args: args pass
 */

void handle_echo_env(char *args[]) 
{
	int i;
    if (args[1] == NULL || args[2] != NULL) 
	{
        char err_msg[] = "Usage: echo $VARIABLE\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));
    } 
	else 
	{
        char *variable = args[1] + 1; /* Skip the '$' character */

        if (strcmp(variable, "?") == 0) 
		{
            int exit_status = WEXITSTATUS(get_exit_status());
            char exit_status_str[10];
            int num_digits = 0;

            if (exit_status == 0) 
			{
                exit_status_str[0] = '0';
                num_digits = 1;
            } 
			else 
			{
                while (exit_status > 0) 
				{
                    exit_status_str[num_digits++] = '0' + (exit_status % 10);
                    exit_status /= 10;
                }
            }

            for (i = num_digits - 1; i >= 0; i--) 
			{
                write(STDOUT_FILENO, &exit_status_str[i], 1);
            }
            write(STDOUT_FILENO, "\n", 1);
        } 
		else if (strcmp(variable, "PATH") == 0) 
		{
            char *path = getenv("PATH");
            if (path != NULL) 
			{
                write(STDOUT_FILENO, path, strlen(path));
                write(STDOUT_FILENO, "\n", 1);
            } 
			else 
			{
                write(STDERR_FILENO, "PATH not set\n", strlen("PATH not set\n"));
            }
        } 
		else 
		{
            char *value = getenv(variable);
            if (value != NULL) 
			{
                write(STDOUT_FILENO, value, strlen(value));
                write(STDOUT_FILENO, "\n", 1);
            } 
			else 
			{
                char err_msg[50];
                strcpy(err_msg, variable);
                strcat(err_msg, ": Undefined variable\n");
                write(STDERR_FILENO, err_msg, strlen(err_msg));
            }
        }
    }
}
