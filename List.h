#ifndef LIST_H
#define LIST_H

#include <stddef.h>

int exe_com(char *comnd, char **args);
char *find_comnd(char *comnd, char **paths);
int exe_with_path(char *comnd, char **args, char **envp);
void exit_shell(void);
void print_evnt(char **envp);
size_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void exe_comnds_sept(char *input, char **envp);
void exe_logic_op(char *comnd, char **envp, int logic_op);
int set_shell_var(char *var, char *valu);
int unset_shell_var(char *var);
int ch_dir(char *path);
void rem_comnts(char *input);
void exe_comnds_4rm_file(char *fname, char **envp);
void run_shell(char **envp);

#endif /* LIST_H */
