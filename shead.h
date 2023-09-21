#ifndef SHEAD_H
#define SHEAD_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"


#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int custom_read(char **buffer);
void custom_write(char *buffer);
void execute_command(char *args[]);
int parse_command(char *input, char *args[]);
void handle_cd(char *args[]);
void handle_exit(char *args[]);
int get_exit_status(void);
char *special_variable(char *var);
void handle_setenv(char *args[]);
void handle_unsetenv(char *args[]);
void handle_echo_env(char *args[]);

#endif /* SHEAD_H */