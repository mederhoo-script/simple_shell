#include "shead.h"
#include <unistd.h>

int main(void)
{
    char *command;
    char *full_path;
    char not_found_message[64];
    ssize_t message_length;

    command = read_it();
    if (command == NULL)
    {
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }

    full_path = find_exe(command);
    if (full_path != NULL)
    {
        exe_com(full_path);
        free(full_path);
    }
    else
    {
        message_length = snprintf(not_found_message, sizeof(not_found_message), "Command not found: %s\n", command);
        if (message_length < 0 || (size_t)message_length >= sizeof(not_found_message))
        {
            perror("Error creating not found message");
            free(command);
            return 1;
        }
        write(STDOUT_FILENO, not_found_message, message_length);
    }

    free(command);
    return 0;
}
