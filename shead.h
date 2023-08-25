#ifndef SHEAD_H
#define SHEAD_H

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



void handle_input(char **input, size_t *input_size);
void handle_prompt(char **input, size_t *input_size);
int handle_getline(char **input, size_t *input_size, ssize_t *getline_result);
int handle_empty_input(const char *input);
void handle_cleanup(char **args, char *input);
int is_pipe_input(void);
void handle_construct_path(char *path, const char *input);
int handle_fork(pid_t pid);
void handle_child_or_parent(pid_t pid, const char *input);
int execute_command(const char *input);

#endif /* SHEAD_H */
