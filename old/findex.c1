#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shead.h"

#define MAX_PATH_LENGTH 4096

/**
 * find_exe - Search for the executable path.
 * @command: The command.
 *
 * Return: A pointer to the full path if found, or NULL if not found.
 */
char *find_exe(const char *command)
{
    char *path;
    char *path_copy;
    char *token;
    char full_path[MAX_PATH_LENGTH];
    char *result = NULL;

    path = getenv("PATH");
    if (path == NULL)
    {
        return (NULL);
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        int path_len = strlen(token);
        int cmd_len = strlen(command);

        if (path_len + cmd_len + 2 <= MAX_PATH_LENGTH)
        {
            strcpy(full_path, token);
            strcat(full_path, "/");
            strcat(full_path, command);

            if (access(full_path, X_OK) == 0)
            {
                result = strdup(full_path);
                break;
            }
        }

        token = strtok(NULL, ":");
    }

    free(path_copy);
    return result;
}
