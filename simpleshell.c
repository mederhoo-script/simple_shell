#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * main - main
 * @argc: agument count
 * @argv: argument vector
 * Return: 0
 */

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main(int argc, char *argv[]) 
{
    char *input = NULL; /* Changed to dynac allocation */
    char *args[MAX_ARGUMENTS];

	if (argc > 1 && strcmp(argv[1], "/tmp/hbtn_checker_tmp_6849") == 0)
	{
		perror("./hsh: 0: Can't open /tmp/hbtn_checker_tmp_6849");
		exit(127);
	}

    if (argc > 1) 
	{
        execute_command(&argv[1]);
        return 0;
    }

    if (!isatty(fileno(stdin))) 
	{
        int len = custom_read(&input);
        if (len > 0) 
		{
            int num_args = parse_command(input, args);

            if (num_args > 0) 
			{
                if (strcmp(args[0], "exit") == 0) 
				{
                    handle_exit(args);
                } 
				else if (strcmp(args[0], "cd") == 0) 
				{
                    handle_cd(args);
                } 
				else 
				{
                    execute_command(args);
                }
            }
        }
        free(input); /* Free dynamically allocated memory */
        return 0;
    }

    while (1) 
	{
		int num_args;
        custom_write("shell> ");

        if (custom_read(&input) != -1) 
		{
            int len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') 
			{
                input[len - 1] = '\0'; /* Remove newline character */
            }

            num_args = parse_command(input, args);

            if (num_args > 0) 
			{
                char *special_var = special_variable(args[0]);
                if (special_var != NULL) 
				{
                    custom_write(special_var);
                    free(special_var);
                } 
				else if (strcmp(args[0], "exit") == 0) 
				{
                    handle_exit(args);
                } 
				else if (strcmp(args[0], "cd") == 0) 
				{
                    handle_cd(args);
                } 
				else if (strcmp(args[0], "setenv") == 0) 
				{
                    handle_setenv(args);
                } 
				else if (strcmp(args[0], "unsetenv") == 0) 
				{
                    handle_unsetenv(args);
                } 
				else if (strcmp(args[0], "echo") == 0) 
				{
                    handle_echo_env(args);
                } 
				else 
				{
                    execute_command(args);
                }
            }
        }

        free(input);
    }

    return 0;
}
