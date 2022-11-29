/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:16:52 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/28 22:15:50 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_closing_char(t_ms *ms, char open, char close)
{
	int		has_closed_quote;
	char	*buff_ptr;

	buff_ptr = ms->buffer;
	has_closed_quote = *buff_ptr == open 
		&& ft_strchr(++buff_ptr, close);
	return (has_closed_quote);
}

char	*ft_create_token_string(t_ms *ms, size_t len)
{
	char	*tok;

	tok = ft_substr(ms->buffer - len, 0, len);
	return (tok);
}


t_token		*ft_return_simple_token(t_ms *ms, char *token_string,
				t_token_type token_type)
{
	t_token	*token;
	size_t	index;		
	
	index = ft_strlen(token_string);
	ms->buffer = ms->buffer + index;
	token = ft_create_token_node(token_string, token_type);
	return (token);
}

int	ft_advance_ptr_after_white_space(char **buffer)
{
	size_t	len;

	len = 0;
	while (ft_strchr(WHITE_SPACE, **buffer) && **buffer)
	{
		(*buffer)++;
		len++;
	}
	return (len);
}

size_t	ft_advance_ptr_until_char(char **buf, char ch)
{
	size_t	len;

	len = 0;
	while(**buf && **buf != ch)
	{
		(*buf)++;
		len++;
	}
	return (len);
}

void	ft_deal_unclosed_char(t_ms *ms, char close_char)
{
	char 	*line;
	char	*line_acc;
	size_t	index;

	index = 0;
	line_acc = ft_strdup("");
	while (TRUE)
	{
		line = readline(UNCLOSED_QUOTE);
		line = ft_strjoin_free(ft_strdup("\n"), line);
		line_acc = ft_strjoin_free(line_acc, line);
		if (ft_strchr(line_acc, close_char))
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

char	*ft_open_close_token_handler(t_ms *ms, char open_char, char close_char)
{
	char	*word;
	size_t	len;

	word = NULL;
	if (!has_closing_char(ms, open_char, close_char))
		ft_deal_unclosed_char(ms, close_char);
	ms->buffer++;
	len = ft_advance_ptr_until_char(&ms->buffer, close_char);
	word = ft_create_token_string(ms, len);
	return (word);
}
