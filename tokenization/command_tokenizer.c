/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:26:52 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:28:52 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_command(char *buffer)
{
	if (!ft_strchr(WHITE_SPACE, *buffer))
		return (WORD);
	return (NOT_FOUND);
}

t_token	*ft_create_command_token_with_quote(t_ms *ms, size_t *len)
{
	t_token		*command;

	if (ft_strncmp(ms->buffer, EMPTY_DOUBLE_QUOTE, 2) == 0
		|| ft_strncmp(ms->buffer, EMPTY_SINGLE_QUOTE, 2) == 0)
	{
		ms->buffer = ms->buffer + 2;
		*len = *len + 2;
		return (NULL);
	}
	command = ft_quoting_tokenizer(ms);
	if (!command)
		return (NULL);
	command->type = WORD;
	return (command);
}

size_t	ft_adv_ptr_after_quote(t_ms *ms, t_token **cmd_quote)
{
	char			*pos;
	size_t			len;

	len = 0;
	while (*ms->buffer && !ft_strchr(WHITE_SPACE, *ms->buffer)
		&& !ft_strchr(OPERATORS, *ms->buffer))
	{
		pos = ms->buffer;
		*cmd_quote = ft_create_command_token_with_quote(ms, &len);
		if (*cmd_quote)
		{
			ms->buffer = pos;
			break ;
		}
		len++;
		ms->buffer++;
	}
	return (len);
}

void	ft_remove_empty_quoting(char **tok, char *quoting_str)
{
	char	*removed_empty_quote_tok;
	t_bool	should_free;

	removed_empty_quote_tok = ft_strdup(*tok);
	should_free = TRUE;
	while (ft_strnstr(*tok, quoting_str, ft_strlen(*tok)))
	{
		should_free = FALSE;
		removed_empty_quote_tok = ft_replace_str(*tok, quoting_str, "");
		ft_free_ptr((void **)&(*tok));
		*tok = ft_strdup(removed_empty_quote_tok);
		ft_free_ptr((void **)&(removed_empty_quote_tok));
	}
	if (should_free)
		ft_free_ptr((void **)&(removed_empty_quote_tok));
}

t_token	*ft_command_tokenizer(t_ms *ms)
{
	t_token			*command;
	t_token			*cmd_quote;
	char			*tok;

	cmd_quote = NULL;
	if (ft_strchr(OPERATORS, *ms->buffer))
	{
		ms->invalid_program = SYNTAX_ERR;
		return (NULL);
	}
	tok = ft_create_token_string(ms, ft_adv_ptr_after_quote(ms, &cmd_quote));
	if (cmd_quote)
	{
		tok = ft_strjoin_free(tok, ft_strdup(cmd_quote->token));
		ms->buffer += ft_strlen(cmd_quote->token) + 2;
	}
	ft_remove_empty_quoting(&tok, EMPTY_DOUBLE_QUOTE);
	ft_remove_empty_quoting(&tok, EMPTY_SINGLE_QUOTE);
	command = ft_create_token_node(tok, WORD);
	if (cmd_quote)
		command->should_expand = cmd_quote->should_expand;
	ft_delete_token(cmd_quote);
	ft_advance_ptr_after_white_space(&ms->buffer);
	return (command);
}
