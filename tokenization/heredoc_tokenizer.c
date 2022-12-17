/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:53:47 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/15 16:08:39 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_heredoc(char *buffer)
{
	if (ft_strncmp(buffer, DLESS, ft_strlen(DLESS)) == 0)
		return (IO_HEREDOC);
	return (NOT_FOUND);
}

t_token		*ft_heredoc_tokenizer(t_ms *ms)
{
	t_token			*heredoc;
	char			*tok;
	t_token_type	type;
	size_t			len;

	ms->buffer = (ms->buffer + 2);
	type = IO_HEREDOC;
	len = 0;
	ft_advance_ptr_after_white_space(&ms->buffer);
	while (!ft_strchr(WHITE_SPACE, *ms->buffer))
	{
		len++;
		ms->buffer++;
	}
	tok = ft_create_token_string(ms, len);
	heredoc = ft_create_token_node(tok, type);
	ft_heredoc_handler(ms,
		&(t_file){NOT_FOUND_FD, HEREDOC_FILE, HEREDOC, tok});
	return (heredoc);
}
