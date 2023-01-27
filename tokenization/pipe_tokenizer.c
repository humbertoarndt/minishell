/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:22:30 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 11:42:38 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_pipe(char *buffer)
{
	if (ft_strncmp(buffer, PIPE, ft_strlen(PIPE)) == 0)
		return (PIPELINE);
	return (NOT_FOUND);
}

t_token	*ft_pipe_tokenizer(t_ms *ms)
{
	t_token			*pipe;

	pipe = ft_return_simple_token(ms, ft_strdup(PIPE), PIPELINE);
	ms->ctr.pipe_count++;
	ft_advance_ptr_after_white_space(&ms->buffer);
	return (pipe);
}
