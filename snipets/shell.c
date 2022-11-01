#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

//compiles this code using
//cc -g -lreadline shell.c -o shell && ./shell

static sigjmp_buf env;
static volatile sig_atomic_t	jump_active = 0;
typedef struct sigaction		t_sigaction;
typedef void					(*t_sighandler)(int);
t_sighandler	signal(int signum, t_sighandler handler);

void	sigint_handler(int signo)
{
	if (!jump_active)
		return ;
	siglongjmp(env, 42);
}

/**
 * @brief Changes directory
 * 
 * @param path The path to follows
 * @return int 0 on sucess, or >0 if an error occurs
 */
int	cd(char *path)
{
	return (chdir(path));
}

/**
 * @brief Get the input object
 * 
 * @param input The string received as argument
 * @return char** An array os strings trimmed by " "
 */
char	**get_input(char *input)
{
	char		**command;
	char		*separator;
	char		*parsed;
	int			index;

	command = (char **)malloc(8 * sizeof(char **));
	if (!command)
	{
		perror("malloc failed\n");
		exit(1);
	}
	separator = " ";
	index = 0;
	parsed = strtok(input, separator);
	while (parsed != NULL)
	{
		command[index] = parsed;
		index++;
		parsed = strtok(NULL, separator);
	}
	command[index] = NULL;
	return (command);
}

int	main(void)
{
	char		**command;
	char		*input;
	pid_t		child_pid;
	int			stat_loc;
	t_sigaction	s;
	t_sigaction	s_child;

	s.sa_handler = sigint_handler;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s, NULL);
	while (1)
	{
		if (sigsetjmp(env, 1) == 42)
		{
			printf("\n");
			continue ;
		}
		jump_active = 1;
		input = readline("\033[1;35munixsh>\033[1;0m ");
		if (input == NULL)
		{
			printf("\n");
			exit (0);
		}
		command = get_input(input);
		if (!command[0])
		{
			free(input);
			free(command);
			continue ;
		}
		if (strcmp(command[0], "cd") == 0)
		{
			if (cd(command[1]) < 0)
				perror(command[1]);
			continue ;
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Fork failed.\n");
			exit(1);
		}
		if (child_pid == 0)
		{
			s_child.sa_handler = sigint_handler;
			sigemptyset(&s_child.sa_mask);
			s_child.sa_flags = SA_RESTART;
			sigaction(SIGINT, &s_child, NULL);
			if (execvp(command[0], command) < 0)
			{
				perror(command[0]);
				exit(1);
			}
		}
		else
			waitpid(child_pid, &stat_loc, WUNTRACED);
		if (!input)
			free(input);
		if (!command)
			free(command);
	}
	return (0);
}
