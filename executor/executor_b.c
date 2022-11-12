/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/12 15:04:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_execute_tree(t_ms *ms, t_executor *exec_tree);

void	ft_exec_cmds(t_ms *ms, t_executor *exec_tree)
{
	t_list		*pid_list;
	pid_t		*pid;
	char		**envp;

	if (!exec_tree)
		return ;
	ft_build_cmds(exec_tree->cmds, ms->env.path);
	if (exec_tree->cmds->cmd_index == ms->ctr.cmds_count - 1)
		ms->should_pipe = FALSE;
	ft_printf("cmd: %s | should_write: %d |should_pipe: %d\n", exec_tree->cmds->cmd,ms->should_write, ms->should_pipe);
	pid = (pid_t *)malloc(sizeof(pid_t));
	*pid = fork();
	if (*pid == ERROR_CODE_FUNCTION)
		exit(1);//implementar error handler
	if (*pid == CHILD_PROCESS)
	{
		if (ms->should_write == FALSE)
		{
			if (ms->fd_pipe[READ_FD] != INIT_FD)
			{
				ft_close_fd(ms->fd_pipe[WRITE_FD]);
				dup2(ms->fd_pipe[READ_FD], STDIN_FILENO);
				ft_close_fd(ms->fd_pipe[READ_FD]);
			}
		}
		else
		{
			if (ms->fd_pipe[WRITE_FD] != INIT_FD)
			{
				ft_close_fd(ms->fd_pipe[READ_FD]);
				dup2(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
				ft_close_fd(ms->fd_pipe[WRITE_FD]);
			}	
		}
		envp = ft_rebuild_envp(ms->env.var);
		execve(exec_tree->cmds->cmd, exec_tree->cmds->argv, envp);
		ft_free_matrix((void ***)&(envp));
	}
	else
	{
		pid_list = ft_lstnew(pid);
		ft_lstadd_back(&ms->pids, pid_list);
	}
}

void	ft_execute_pipe(t_ms *ms, t_executor *exec_tree)
{
	if (pipe(ms->fd_pipe) == ERROR_CODE_FUNCTION)
		exit(1);//implementar error handler
	
	ms->should_pipe = TRUE;
	ft_execute_tree(ms, exec_tree->left);
	ms->should_write = ms->should_write ^ 1;
	ft_execute_tree(ms, exec_tree->right);
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

	ft_dup_stdin_out(ms);
	ft_execute_tree(ms, ms->executor);
	ft_restore_stdin_out(ms);
	pids = ms->pids;
	ft_close_fd(ms->fd_pipe[WRITE_FD]);
	ft_close_fd(ms->fd_pipe[READ_FD]);
	while (pids)
	{
		waitpid((*(pid_t *)pids->content), &ms->exit_code, 0);
		if (WIFEXITED(ms->exit_code))
			ms->exit_code = WEXITSTATUS(ms->exit_code);
		pids = pids->next;
	}
	return ;
}