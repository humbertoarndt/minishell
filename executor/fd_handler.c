/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:52:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/12 17:07:19 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int fd)
{
	if (fd < 0)
		return ;
	close(fd);
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

void	ft_handle_pipes(t_ms *ms, t_executor *exec_tree)
{
	if (ms->ctr.pipe_count == 0)
		return ;
	if (exec_tree->cmds->cmd_index == 0)
	{
		ft_close_fd(ms->fd_pipe[READ_FD]);
		dup2(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
		ft_close_fd(ms->fd_pipe[WRITE_FD]);
	}
	else if (exec_tree->cmds->cmd_index != ms->ctr.cmds_count - 1)
	{
		ft_close_fd(ms->prev_fd_pipe[WRITE_FD]);
		ft_close_fd(ms->fd_pipe[READ_FD]);
		dup2(ms->prev_fd_pipe[READ_FD], STDIN_FILENO);
		ft_close_fd(ms->prev_fd_pipe[READ_FD]);
		dup2(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
		ft_close_fd(ms->fd_pipe[WRITE_FD]);
	}
	else if (exec_tree->cmds->cmd_index == ms->ctr.cmds_count - 1)
	{
		ft_close_fd(ms->fd_pipe[WRITE_FD]);
		dup2(ms->fd_pipe[READ_FD], STDIN_FILENO);
		ft_close_fd(ms->fd_pipe[READ_FD]);
	}
}