/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:51:13 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 21:51:29 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_pipes(t_ms *ms)
{
	if (ms->ctr.pipe_count == 0 || ms->ctr.pipe_start < 0)
		return ;
	if (ms->ctr.pipe_start == 0)
	{
		ft_close_fd(ms->fd_pipe[READ_FD]);
		ft_dup2_and_close(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
	}
	else if (ms->ctr.pipe_start != ms->ctr.pipe_count)
	{
		ft_close_fd(ms->prev_fd_pipe[WRITE_FD]);
		ft_close_fd(ms->fd_pipe[READ_FD]);
		ft_dup2_and_close(ms->prev_fd_pipe[READ_FD], STDIN_FILENO);
		ft_dup2_and_close(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
	}
	else if (ms->ctr.pipe_start == ms->ctr.pipe_count)
	{
		ft_close_fd(ms->fd_pipe[WRITE_FD]);
		ft_dup2_and_close(ms->fd_pipe[READ_FD], STDIN_FILENO);
	}
}

void	ft_init_pipes(t_ms *ms)
{
	if (ms->should_pipe)
	{
		ms->ctr.pipe_start++;
		ft_close_pipe_fds(ms->prev_fd_pipe);
		if (ms->ctr.pipe_start == ms->ctr.pipe_count)
			return ;
		ft_copy_fds_pipe_to_previous(ms->fd_pipe, ms->prev_fd_pipe);
		if (pipe(ms->fd_pipe) == ERROR_CODE_FUNCTION)
			exit(1);
	}
}
