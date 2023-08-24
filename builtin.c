#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * builtin_env - Print the environment variables.
 */
void builtin_env(void)
{
    char **env;
    
    env = environ;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}
