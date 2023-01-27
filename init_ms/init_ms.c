/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:48:56 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 11:55:00 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{
	ms->buffer = NULL;
	ms->buffer_start = NULL;
	ms->tokens = NULL;
	ms->invalid_program = FALSE;
	ms->executor = NULL;
	ms->pids = NULL;
	ms->should_pipe = FALSE;
	ms->stdin_out.stdin = STDIN_FILENO;
	ms->stdin_out.stdout = STDOUT_FILENO;
	ms->ctr.pipe_count = 0;
	ms->ctr.cmds_count = 0;
	ms->ctr.index = 0;
	ms->ctr.pipe_start = -1;
	ms->fd_pipe[WRITE_FD] = NOT_FOUND_FD;
	ms->fd_pipe[READ_FD] = NOT_FOUND_FD;
	ms->prev_fd_pipe[WRITE_FD] = NOT_FOUND_FD;
	ms->prev_fd_pipe[READ_FD] = NOT_FOUND_FD;
	ms->prompt_str = NULL;
}

void	ft_init_env(t_ms *ms, char *envp[])
{
	ms->env.var = NULL;
	ms->env.envp = envp;
}
