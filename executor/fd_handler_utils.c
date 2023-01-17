/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:52:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 21:56:26 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe_fds(int fd[2])
{
	ft_close_fd(fd[WRITE_FD]);
	ft_close_fd(fd[READ_FD]);
}

void	ft_dup2_and_close(int fd_to_close, int fd_to_dup)
{
	dup2(fd_to_close, fd_to_dup);
	ft_close_fd(fd_to_close);
}

void	ft_dup_stdin_out(t_ms *ms)
{
	ms->stdin_out.stdin = dup(STDIN_FILENO);
	ms->stdin_out.stdout = dup(STDOUT_FILENO);
}

void	ft_restore_stdin_out(t_ms *ms)
{
	ft_dup2_and_close(ms->stdin_out.stdin, STDIN_FILENO);
	ft_dup2_and_close(ms->stdin_out.stdout, STDOUT_FILENO);
}

void	ft_copy_fds_pipe_to_previous(int fd[2], int prev_fd[2])
{
	prev_fd[0] = fd[0];
	prev_fd[1] = fd[1];
}
