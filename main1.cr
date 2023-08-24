#include "shead.h"
#include <unistd.h>

int main(void)
{
    

    char *command = read_it();
    if (command == NULL)
    {
        write(STDOUT_FILENO, "\n", 1);
        break;
    }

    char *full_path = find_executable(command);
    if (full_path != NULL)
    {
        exe_com(full_path);
        free(full_path);
    }
    else
    {
        char not_found_message[64];
        snprintf(not_found_message, sizeof(not_found_message), "Command not found: %s\n", command);
        write(STDOUT_FILENO, not_found_message, strlen(not_found_message));
    }

    free(command);

    
}
