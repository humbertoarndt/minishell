#include "stdio.h"
#include "unistd.h"
#include "wait.h"
int main()
{
	int c;
	int status;

	c = 500;
	pid_t pid = fork();
	
	if (pid == 0)
	{
		char  *cmd[] = {"echo", "nsjansja", NULL};
		execve("/usr/bin/echo", cmd, NULL);
	}
	else
	{
		waitpid(pid,&status, 0);
		printf("PROCESSO PAI%d", pid);
	}
	return (0);
}
