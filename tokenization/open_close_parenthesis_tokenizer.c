/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_parenthesis_tokenizer.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:37:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/28 23:36:34 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_open_close_parenthesis_quoting(char *buffer)
{
	if (*buffer == SINGLE_QUOTE_CHAR)
		return (SINGLE_QUOTE);
	if (*buffer == DOUBLE_QUOTE_CHAR)
		return (DOUBLE_QUOTE);
	if (*buffer == OPEN_PARENTHESIS_CHAR)
		return (PARENTHESIS);
	if (*buffer == CLOSE_PARENTHESIS_CHAR)
		return (PARENTHESIS);
	return (NOT_FOUND);
}

char	*ft_deal_quote(t_ms *ms, t_token_type type, int *should_expand)
{
	char	*tok;

	tok = NULL;
	if (type == SINGLE_QUOTE)
	{
		tok = ft_open_close_token_handler(ms, SINGLE_QUOTE_CHAR,
				SINGLE_QUOTE_CHAR);
		*should_expand = FALSE;
	}
	else if (type == DOUBLE_QUOTE)
	{
		tok = ft_open_close_token_handler(ms, DOUBLE_QUOTE_CHAR,
				DOUBLE_QUOTE_CHAR);
		*should_expand = TRUE;
	}
	return (tok);
}

char	*ft_deal_parenthesis(t_ms *ms, t_token_type type, int *should_expand)
{
	char	*tok;

	tok = NULL;
	if (type == PARENTHESIS)
	{
		if (ms->buffer_start == ms->buffer)
			*should_expand = FALSE;
		else if (*(ms->buffer - 1) == VARIABLE_EXPRESSION[0])
			*should_expand = TRUE;
		else
			*should_expand = FALSE;
		tok = ft_open_close_token_handler(ms,  OPEN_PARENTHESIS_CHAR,
				CLOSE_PARENTHESIS_CHAR);
		ms->has_subshell = TRUE;
	}
	return (tok);
}

t_token	*ft_open_close_parenthesis_tokenizer(t_ms *ms)
{
	t_token 		*quote_or_parenth;
	char			*tok;
	t_token_type	type;
	int				should_expand;

	tok = NULL;
	type = ft_open_close_parenthesis_quoting(ms->buffer);
	should_expand = FALSE;
	tok = ft_deal_quote(ms, type, &should_expand);
	if (tok == NULL)
		tok = ft_deal_parenthesis(ms, type, &should_expand);
	if (tok == NULL)
		return (NULL);
	quote_or_parenth = ft_create_token_node(tok, type);
	quote_or_parenth->should_expand = should_expand;
	return (quote_or_parenth);
}

