/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor copy 2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/12 00:34:55 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	ft_exec_cmds(t_ms *ms, t_executor *exec_tree)
{
	t_list	*pid_list;
	pid_t		*pid;
	char		**envp;
	int			fd_index;

	if (!exec_tree)
		return ;
	ft_build_cmds(&exec_tree->cmds, ms->env.path);
	pid = malloc(sizeof(pid_t));
	*pid = fork();
	fd_index = exec_tree->depth;
	if (*pid == ERROR_CODE_FUNCTION)
		exit(1);//implementar error handler
	if (*pid == CHILD_PROCESS)
	{
		if (ms->should_write == FALSE)
		{
			if (ms->fd_pipes[fd_index].fd[READ_FD] != -2)
			{
				ft_close_fd(ms->fd_pipes[fd_index].fd[WRITE_FD]);
				dup2(ms->fd_pipes[fd_index].fd[READ_FD], STDIN_FILENO);
				ft_close_fd(ms->fd_pipes[fd_index].fd[READ_FD]);
			}
		}
		else
		{
			if (ms->fd_pipes[fd_index].fd[WRITE_FD] != -2)
			{
				ft_close_fd(ms->fd_pipes[fd_index].fd[READ_FD]);
				dup2(ms->fd_pipes[fd_index].fd[WRITE_FD], STDOUT_FILENO);
				ft_close_fd(ms->fd_pipes[fd_index].fd[WRITE_FD]);
			}	
			
		}
		envp = ft_rebuild_envp(ms->env.var);
		execve(exec_tree->cmds.cmd, exec_tree->cmds.argv, envp);
		ft_free_matrix((void ***)&(envp));
	}
	else
	{
		pid_list = ft_lstnew(pid);
		ft_lstadd_back(&ms->pids, pid_list);
	}
	
}

void	ft_dup_stdin_out(t_ms *ms)
{
	ms->stdin_out.stdin = dup(STDIN_FILENO);
	ms->stdin_out.stdout = dup(STDOUT_FILENO);
}

void	ft_restore_stdin_out(t_ms *ms)
{
	dup2(ms->stdin_out.stdin, STDIN_FILENO);
	close(ms->stdin_out.stdin);
	dup2(ms->stdin_out.stdout, STDOUT_FILENO);
	close(ms->stdin_out.stdin);
}

void	ft_execute_pipe(t_ms *ms, t_executor *exec_tree)
{
	int	fd_index;

	fd_index = ms->index;
	if (pipe(ms->fd_pipes[fd_index].fd) == ERROR_CODE_FUNCTION)
		exit(1);//implementar error handler
	ft_execute_tree(ms, exec_tree->left);
	ms->should_write = ms->should_write ^ 1;
	ft_execute_tree(ms, exec_tree->right);
	ft_close_fd(ms->fd_pipes[fd_index].fd[WRITE_FD]);
	ft_close_fd(ms->fd_pipes[fd_index].fd[READ_FD]);
	ms->index++;
}

void	ft_execute_tree(t_ms *ms, t_executor *exec_tree)
{
	if (!exec_tree)
		return ;
	if (exec_tree->operator &&
		ft_strncmp(exec_tree->operator, PIPE, ft_strlen(PIPE)) == 0)
		ft_execute_pipe(ms, exec_tree);
	else
		ft_exec_cmds(ms, exec_tree);
}

void	ft_execute(t_ms *ms)
{
	t_list			*pids;
	int				index;

	ft_dup_stdin_out(ms);
	ft_init_fd_pipes(ms);
	ms->index = 0;
	ft_execute_tree(ms, ms->executor);
	ft_restore_stdin_out(ms);
	pids = ms->pids;
	index = 0;
	while (index < ms->ctr.pipe_count)
	{
		ft_close_fd(ms->fd_pipes[index].fd[WRITE_FD]);
		ft_close_fd(ms->fd_pipes[index].fd[READ_FD]);
		index++;
	}
	while (pids)
	{
		waitpid((*(pid_t *)pids->content), &ms->exit_code, 0);
		if (WIFEXITED(ms->exit_code))
			ms->exit_code = WEXITSTATUS(ms->exit_code);
		pids = pids->next;
	}
	return ;
}