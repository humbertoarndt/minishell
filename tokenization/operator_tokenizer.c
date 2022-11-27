/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:22:30 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/26 17:58:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_operator(char *buffer)
{
	if (ft_strncmp(buffer, PIPE, ft_strlen(PIPE)) == 0 
		&& ft_strncmp(buffer, AND_OR_OP, ft_strlen(AND_OR_OP)) != 0)
		return (PIPELINE);
	if (ft_strncmp(buffer, AND_IF_OP, ft_strlen(AND_IF_OP)) == 0)
		return (AND_IF);
	if (ft_strncmp(buffer, AND_OR_OP, ft_strlen(AND_OR_OP)) == 0)
		return (OR_IF);
	return (NOT_FOUND);
}

char	*ft_return_operator_str(t_token_type type)
{
	if (type == PIPELINE)
		return (PIPE);
	if (type == AND_IF)
		return (AND_IF_OP);
	if (type == OR_IF)
		return (AND_OR_OP);
	return (NULL);
}

t_token	*ft_operator_tokenizer(t_ms *ms)
{
	t_token			*operator;
	t_token_type	type;
	char			*token;

	type = ft_found_operator(ms->buffer);
	if (type == PIPELINE)
		ms->ctr.pipe_count++;
	token = ft_return_operator_str(type);
	if (!token)
		return (NULL);
	operator = ft_return_simple_token(ms, ft_strdup(token), type);
	return (operator);
}
