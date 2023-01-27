/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:16:52 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:06:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_closing_char(t_ms *ms, char quote)
{
	int		has_closed_quote;
	char	*buff_ptr;

	buff_ptr = ms->buffer;
	has_closed_quote = (*buff_ptr == quote && ft_strchr(++buff_ptr, quote));
	return (has_closed_quote);
}

char	*ft_create_token_string(t_ms *ms, size_t len)
{
	char	*tok;

	tok = ft_substr(ms->buffer - len, 0, len);
	return (tok);
}

t_token	*ft_return_simple_token(t_ms *ms, char *token_string,
				t_token_type token_type)
{
	t_token	*token;

	ms->buffer++;
	token = ft_create_token_node(token_string, token_type);
	return (token);
}

int	ft_advance_ptr_after_white_space(char **buffer)
{
	size_t	len;

	len = 0;
	while (**buffer && ft_strchr(WHITE_SPACE, **buffer))
	{
		(*buffer)++;
		len++;
	}
	return (len);
}

size_t	ft_advance_ptr_until_quote(char **buf, char quote)
{
	size_t	len;
	char	*quote_str;

	len = 0;
	if (quote == '\'')
		quote_str = EMPTY_SINGLE_QUOTE;
	else
		quote_str = EMPTY_DOUBLE_QUOTE;
	while (**buf)
	{
		if (ft_strncmp(*buf, quote_str, 2) == 0)
		{
			*buf = *buf + 2;
			len += 2;
			continue ;
		}
		if (**buf == quote)
			break ;
		(*buf)++;
		len++;
	}
	return (len);
}
