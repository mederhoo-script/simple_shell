#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "shead.h"


int get_exit_status(void)
{
	int exit_status;

	wait(&exit_status);
	return (exit_status);
}
