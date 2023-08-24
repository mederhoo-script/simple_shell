#ifndef SHEAD_H
#define SHEAD_H

void prompt_out(void);
char *read_it(void);
void exe_com(const char *command, char **args);
char *find_exe(const char *command);
char **read_command_with_args(void);
void builtin_env(void);

#endif /* SHEAD_H */
