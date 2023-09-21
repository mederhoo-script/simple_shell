#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int custom_read(char *buffer, int size) {
    int i = 0;
    char c;
    while (i < size - 1 && read(STDIN_FILENO, &c, 1) && c != '\n') {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    return i;
}

void custom_write(char *buffer) {
    int i = 0;
    while (buffer[i] != '\0') {
        write(STDOUT_FILENO, &buffer[i], 1);
        i++;
    }
}

void execute_command(char *args[]) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(args[0], args, NULL) == -1) {
            perror("shell");
        }
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int parse_command(char *input, char *args[]) {
    int i = 0;
    char *token = strtok(input, " \n");

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    return i;
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];

    while (1) {
        custom_write("shell> ");

        int len = custom_read(input, MAX_COMMAND_LENGTH);

        if (len > 0) {
            int num_args = parse_command(input, args);

            if (num_args > 0) {
                if (strcmp(args[0], "exit") == 0) {
                    break; // Exit the shell
                } else {
                    execute_command(args);
                }
            }
        }
    }

    return 0;
}
