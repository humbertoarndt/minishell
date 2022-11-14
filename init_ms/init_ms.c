/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:48:56 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/14 12:08:38 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{
	ms->buffer = NULL;
	ms->buffer_start = NULL;
	ms->tokens = NULL;
	ms->invalid_program = FALSE;
	ms->exit_code = SUCCESS_CODE;
	ms->executor = NULL;
	ms->pids = NULL;
	ms->should_pipe = FALSE;
	ms->stdin_out.stdin = STDIN_FILENO;
	ms->stdin_out.stdout = STDOUT_FILENO;
	ms->ctr.pipe_count = 0;
	ms->ctr.cmds_count = 0;
	ms->ctr.index = 0;
	ms->fd_pipe[WRITE_FD] = NOT_FOUND_FD;
	ms->fd_pipe[READ_FD] = NOT_FOUND_FD;
	ms->prev_fd_pipe[WRITE_FD] = NOT_FOUND_FD;
	ms->prev_fd_pipe[READ_FD] = NOT_FOUND_FD;
}

void	ft_init_env(t_ms *ms, char *envp[])
{
	ms->env.var = NULL;
	ms->env.envp = envp;
}

// void	ft_init_fd_pipes(t_ms *ms)
// {
// 	int	index;

// 	ms->fd_pipes = (t_pipes_fd*)malloc((sizeof(t_pipes_fd))
// 		* ms->ctr.pipe_count);
// 	while (index < ms->ctr.pipe_count)
// 	{
// 		ms->fd_pipes->fd[WRITE_FD] = INIT_FD;
// 		ms->fd_pipes->fd[READ_FD] = INIT_FD;
// 		index++;
// 	}
// }