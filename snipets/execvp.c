#include <unistd.h>

int	main(void)
{
	char	**argv[] = {"ls", "-l", "-h", "-a", NULL};

	//the compile and execution outputs the same as `ls -l -h -a`
	execvp(argv[0], argv);
	return (0);
}
