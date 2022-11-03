/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:37:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/02 23:43:29 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_dollar_sign(t_ms *ms, char **expanded_str, char quote)
{
	char *exit = ft_replace_str(ms->buffer, "$?", ft_itoa(ms->exit_code));
	ft_printf("%s%s%c", exit ,expanded_str, quote);
}

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
	while(**buf && **buf != quote)
	{
		(*buf)++;
		len++;
	}
	return (len);
}

char	*ft_quote_handler(t_ms *ms, char quote)
{
	char	*quote_word;
	size_t	len;

	quote_word = NULL;
	if (!has_closing_char(ms, quote))
	{
		ms->invalid_program = QUOTING_ERR;
		return (quote_word);
	}
	ms->buffer++;
	len = ft_advance_ptr_until_quote(&ms->buffer, quote);
	quote_word = ft_create_token_string(ms, len);
	return (quote_word);
}

t_token	*ft_quoting_tokenizer(t_ms *ms)
{
	t_token 		*quote;
	char			*tok;
	t_token_type	type;

	if (*ms->buffer == SINGLE_QUOTE_CHAR)
	{
		tok = ft_quote_handler(ms, SINGLE_QUOTE_CHAR);
		type = SINGLE_QUOTE;
	}
	else
	{
		tok = ft_quote_handler(ms, DOUBLE_QUOTE_CHAR);
		type = DOUBLE_QUOTE;
	}
	if (tok == NULL)
		return (NULL);
	quote = ft_create_token_node(tok, type);
	return (quote);
}

