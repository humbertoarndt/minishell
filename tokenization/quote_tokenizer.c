/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:37:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:49:00 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_quoting(char *buffer)
{
	if (*buffer == SINGLE_QUOTE_CHAR)
		return (SINGLE_QUOTE);
	if (*buffer == DOUBLE_QUOTE_CHAR)
		return (DOUBLE_QUOTE);
	return (NOT_FOUND);
}

void	ft_deal_unclosed_quote(t_ms *ms, char quote)
{
	char	*line;
	char	*line_acc;

	line_acc = ft_strdup("");
	line = NULL;
	set_heredoc_signals();
	while (TRUE)
	{
		ft_printf(UNCLOSED_QUOTE);
		line = ft_get_next_line(STDIN_FILENO);
		if (should_stop_on_signals_quoting(ms, line, quote))
		{
			ft_free_ptr((void **)&line);
			ft_free_ptr((void **)&line_acc);
			return ;
		}
		line = ft_strjoin_free(ft_strdup("\n"), line);
		line_acc = ft_strjoin_free(line_acc, line);
		if (ft_strchr(line_acc, quote))
			break ;
	}
	ft_update_buffer(ms, &line_acc);
}

char	*ft_quote_handler(t_ms *ms, char quote)
{
	char	*quote_word;
	size_t	len;

	quote_word = NULL;
	if (!has_closing_char(ms, quote))
		ft_deal_unclosed_quote(ms, quote);
	ms->buffer++;
	len = ft_advance_ptr_until_quote(&ms->buffer, quote);
	quote_word = ft_create_token_string(ms, len);
	return (quote_word);
}

char	*ft_adjust_token_quote(t_ms *ms, char quote, char *quote_str)
{
	char	*tok;

	tok = ft_quote_handler(ms, quote);
	ft_remove_empty_quoting(&tok, quote_str);
	return (tok);
}

t_token	*ft_quoting_tokenizer(t_ms *ms)
{
	t_token			*quote;
	char			*tok;
	t_token_type	type;
	int				should_expand;

	tok = NULL;
	if (*ms->buffer == SINGLE_QUOTE_CHAR)
	{
		tok = ft_adjust_token_quote(ms, SINGLE_QUOTE_CHAR, EMPTY_SINGLE_QUOTE);
		type = SINGLE_QUOTE;
		should_expand = FALSE;
	}
	else if (*ms->buffer == DOUBLE_QUOTE_CHAR)
	{
		tok = ft_adjust_token_quote(ms, DOUBLE_QUOTE_CHAR, EMPTY_DOUBLE_QUOTE);
		type = DOUBLE_QUOTE;
		should_expand = TRUE;
	}
	if (tok == NULL)
		return (NULL);
	quote = ft_create_token_node(tok, type);
	quote->should_expand = should_expand;
	ms->buffer++;
	ft_advance_ptr_after_white_space(&ms->buffer);
	return (quote);
}
