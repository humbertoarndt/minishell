#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	child_pid;
	pid_t	wait_result;
	int		stat_loc;

	child_pid = fork();
	// The child process
	if (child_pid == 0)
	{
		printf("\033[1;32m### Child ###\033[1;0m\nCurrent PID:\t|%d|\nChild PID\t|%d|\n",
			getpid(), child_pid);
		sleep(5); //sleep for one second
	}
	else
	{
		//WUNTRACED return if a child has stopped
		wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
		printf("\033[1;32m### Parent ###\033[1;0m\nCurrent PID:\t|%d|\nChild PID\t|%d|\n",
			getpid(), child_pid);
	}
	return (0);
}
