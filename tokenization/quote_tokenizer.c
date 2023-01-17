/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:37:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 22:11:43 by bbonaldi         ###   ########.fr       */
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

size_t	ft_advance_ptr_until_quote(char **buf, char quote)
{
	size_t	len;

	len = 0;
	while (**buf && **buf != quote)
	{
		(*buf)++;
		len++;
	}
	return (len);
}

void	ft_deal_unclosed_quote(t_ms *ms, char quote)
{
	char	*line;
	char	*line_acc;
	size_t	index;

	index = 0;
	line_acc = ft_strdup("");
	while (TRUE)
	{
		line = readline(UNCLOSED_QUOTE);
		line = ft_strjoin_free(ft_strdup("\n"), line);
		line_acc = ft_strjoin_free(line_acc, line);
		if (ft_strchr(line_acc, quote))
			break ;
	}
	index = ms->buffer - ms->buffer_start;
	ms->buffer_start = ft_strjoin_free(ms->buffer_start, line_acc);
	ms->buffer = ms->buffer_start;
	while (index)
	{	
		ms->buffer++;
		index--;
	}
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

t_token	*ft_quoting_tokenizer(t_ms *ms)
{
	t_token			*quote;
	char			*tok;
	t_token_type	type;
	int				should_expand;

	tok = NULL;
	if (*ms->buffer == SINGLE_QUOTE_CHAR)
	{
		tok = ft_quote_handler(ms, SINGLE_QUOTE_CHAR);
		type = SINGLE_QUOTE;
		should_expand = FALSE;
	}
	else if (*ms->buffer == DOUBLE_QUOTE_CHAR)
	{
		tok = ft_quote_handler(ms, DOUBLE_QUOTE_CHAR);
		type = DOUBLE_QUOTE;
		should_expand = TRUE;
	}
	if (tok == NULL)
		return (NULL);
	quote = ft_create_token_node(tok, type);
	quote->should_expand = should_expand;
	return (quote);
}
