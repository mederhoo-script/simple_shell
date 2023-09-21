#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"


int custom_read(char **buffer) 
{
    size_t size = 0;
    return getline(buffer, &size, stdin);
}