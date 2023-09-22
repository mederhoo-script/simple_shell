#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"

/**
 * custom_write - write
 * @buffer: buffer
 */

void custom_write(char *buffer) 
{
    int i = 0;
    while (buffer[i] != '\0') 
	{
        write(STDOUT_FILENO, &buffer[i], 1);
        i++;
    }
}