/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/05 22:29:38 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_tree(t_ms *ms, t_executor *exec_tree);

void	ft_exec_child(t_ms *ms, t_executor *exec_tree)
{
	char		**envp;

	ft_handle_pipes(ms, exec_tree);
	ft_set_redirection_fds(ms, exec_tree);
	if (!is_builtin(ms, exec_tree, TRUE))
	{
		envp = ft_rebuild_envp(ms->env.var);
		if (!exec_tree->cmds->cmd)
		{
			ft_free_matrix((void ***)&(envp));
			ft_print_custom_error_and_exit(ms, exec_tree->cmds->argv[0],
				COMMAND_NOT_FOUND_ERROR_MSG, COMMAND_NOT_FOUND_ERROR_CODE);
		}
		execve(exec_tree->cmds->cmd, exec_tree->cmds->argv, envp);
		ft_free_matrix((void ***)&(envp));	
	}
}

void	ft_exec_cmds(t_ms *ms, t_executor *exec_tree)
{
	t_list		*pid_list;
	pid_t		*pid;

	if (!exec_tree)
		return ;
	ft_build_cmds(exec_tree->cmds, ms->env.path);
	
	// TODO
	// Checar se linha de comando possui pipe |
	// Se verdadeiro obrigatório forkar; se falso usar o pai
	
	if (ms->should_pipe == FALSE && is_builtin(ms, exec_tree, FALSE))
		return ;
	
	ft_init_pipes(ms, exec_tree);
		
	pid = (pid_t *)malloc(sizeof(pid_t));
	*pid = fork();
	if (*pid == ERROR_CODE_FUNCTION)
		exit(1);//implementar error handler
	if (*pid == CHILD_PROCESS)
	{
		ft_free_ptr((void **)&pid);
		ft_exec_child(ms, exec_tree);
	}
	else
	{
		pid_list = ft_lstnew(pid);
		ft_lstadd_back(&ms->pids, pid_list);
	}
}

void	ft_execute_pipe(t_ms *ms, t_executor *exec_tree)
{
	ms->should_pipe = TRUE;
	ft_execute_tree(ms, exec_tree->left);
	ft_execute_tree(ms, exec_tree->right);
}

void	ft_execute_tree(t_ms *ms, t_executor *exec_tree)
{
	if (!exec_tree)
		return ;
	if (exec_tree->operator
		&& ft_strncmp(exec_tree->operator, PIPE, ft_strlen(PIPE)) == 0)
		ft_execute_pipe(ms, exec_tree);
	else
		ft_exec_cmds(ms, exec_tree);
}


int	ft_wait_childs(t_list *pids)
{
	int	exit_code;

	while (pids)
	{
		waitpid((*(pid_t *)pids->content), &exit_code, 0);
		if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		pids = pids->next;
	}
	return (exit_code);
}

int	ft_execute(t_ms *ms)
{
	int	exit_code;

	ft_dup_stdin_out(ms);
	ft_execute_tree(ms, ms->executor);
	ft_restore_stdin_out(ms);
	ft_close_pipe_fds(ms->fd_pipe);
	exit_code = ft_wait_childs(ms->pids);
	return (exit_code);
}
