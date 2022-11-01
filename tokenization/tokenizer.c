/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:12:20 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/28 18:01:37 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_build_token_list(t_ms *ms)
{
	t_token *token;

	token = NULL;
	if (ft_found_quoting(ms->buffer))
		token = ft_quoting_tokenizer(ms);
	else if (ft_found_redirection(ms->buffer))
		token = ft_io_file_tokenizer(ms);
	else if (ft_found_pipe(ms->buffer))
		token = ft_pipe_tokenizer(ms);
	else if (ft_found_heredoc(ms->buffer))
		token = ft_heredoc_tokenizer(ms);
	else if (ft_found_command(ms->buffer))
		token = ft_command_tokenizer(ms);
	if (token)
		ft_addback_token(&ms->tokens, token);		
}

int	ft_tokenizer(t_ms *ms)
{
	while (ms->buffer && *ms->buffer)
	{
		ft_build_token_list(ms);
		if (ms->buffer && *ms->buffer)
			ms->buffer++;
	}
	return (SUCCESS_CODE);
}
