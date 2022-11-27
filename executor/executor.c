/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/27 19:30:24 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_tree(t_ms *ms, t_executor *exec_tree);

void	ft_exec_child(t_ms *ms, t_executor *exec_tree)
{
	char		**envp;

	ft_handle_pipes(ms);
	ft_set_redirection_fds(ms, exec_tree);
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

void	ft_exec_cmds(t_ms *ms, t_executor *exec_tree)
{
	pid_t		*pid;

	if (!exec_tree || ms->should_exec_next == FALSE)
		return ;
	ft_build_cmds(exec_tree->cmds, ms->env.path);
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
		ft_parent_wait(ms, pid);
}

void	ft_execute_pipe(t_ms *ms, t_executor *exec_tree)
{
	ms->should_pipe = TRUE;
	ft_execute_tree(ms, exec_tree->left);
	ft_execute_tree(ms, exec_tree->right);
}

void	ft_execute_and_or(t_ms *ms, t_executor *exec_tree, t_conditional_op op)
{
	ms->conditional_operator = op;
	ft_execute_tree(ms, exec_tree->left);
	ft_execute_tree(ms, exec_tree->right);
}


void	ft_execute_tree(t_ms *ms, t_executor *exec_tree)
{
	if (!exec_tree)
		return ;
	if (exec_tree->operator
		&& ft_strcmp(exec_tree->operator, PIPE) == 0)
		ft_execute_pipe(ms, exec_tree);
	else if (exec_tree->operator && 
		ft_strcmp(exec_tree->operator, AND_IF_OP) == 0)
		ft_execute_and_or(ms, exec_tree, AND_OP);
	else if (exec_tree->operator && 
		ft_strcmp(exec_tree->operator, AND_OR_OP) == 0)
		ft_execute_and_or(ms, exec_tree, OR_OP);
	else
		ft_exec_cmds(ms, exec_tree);
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
