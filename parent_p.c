#include <sys/wait.h>
#include "shead.h"

/**
 * handle_parent_process - Waits for the completion of a child process.
 *
 *
 * @pid: The PID of the child process to wait for.
 */
void handle_parent_process(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
}
