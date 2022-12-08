/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:26:52 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 22:23:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_command(char *buffer)
{
	if (!ft_strchr(WHITE_SPACE, *buffer))
		return (WORD);
	return (NOT_FOUND);
}

t_token	*ft_command_tokenizer(t_ms *ms)
{
	t_token			*command;
	char			*tok;
	t_token_type	type;
	size_t			len;

	len = 0;
	if (ft_strchr(OPERATORS, *ms->buffer))
	{
		ms->invalid_program = SYNTAX_ERR;
		return (NULL);
	}
	while (!ft_strchr(WHITE_SPACE, *ms->buffer)
		&& !ft_strchr(OPERATORS, *ms->buffer))
	{
		len++;
		ms->buffer++;
	}
	tok = ft_create_token_string(ms, len);
	type = WORD;
	command = ft_create_token_node(tok, type);
	if (ft_strchr(OPERATORS, *ms->buffer))
		ms->buffer--;
	return (command);
}
