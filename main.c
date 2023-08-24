#include "shead.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
    char **command_and_args;
    char *command;
    char *full_path;
    int i;

    while (1)
    {
        prompt_out();

        command_and_args = read_command_with_args();
        if (command_and_args == NULL)
        {
            write(STDOUT_FILENO, "\n", 1);
            break; /* Exit the loop when the user presses Ctrl+D (EOF) */
        }

        command = command_and_args[0];

        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0)
        {
            char exit_message[] = "Exiting the shell...\n";
            write(STDOUT_FILENO, exit_message, strlen(exit_message));
            break; /* Exit the loop when the user enters the "exit" command */
        }
        /* Check if the command is "env" */
        else if (strcmp(command, "env") == 0)
        {
            builtin_env();
        }
        else
        {
            full_path = find_exe(command);
            if (full_path != NULL)
            {
                exe_com(full_path, command_and_args);
                free(full_path);
            }
            else
            {
                char not_found[] = "Command not found: ";
                write(STDOUT_FILENO, not_found, strlen(not_found));
                write(STDOUT_FILENO, command, strlen(command));
                write(STDOUT_FILENO, "\n", 1);
            }
        }

        /* Free allocated memory */
        for (i = 0; command_and_args[i] != NULL; i++)
        {
            free(command_and_args[i]);
        }
        free(command_and_args);
    }

    return 0;
}
