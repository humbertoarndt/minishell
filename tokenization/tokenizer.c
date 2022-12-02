/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:12:20 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/30 22:03:35 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_build_token_list(t_ms *ms, t_token **head)
{
	t_token *token;

	token = NULL;
	if (ft_open_close_parenthesis_quoting(ms->buffer))
		token = ft_open_close_parenthesis_tokenizer(ms);
	else if (ft_found_redirection(ms->buffer))
		token = ft_io_file_tokenizer(ms);
	else if (ft_found_operator(ms->buffer))
		token = ft_operator_tokenizer(ms);
	else if (ft_found_heredoc(ms->buffer))
		token = ft_heredoc_tokenizer(ms);
	else if (ft_found_command(ms->buffer))
		token = ft_command_tokenizer(ms);
	if (token)
		ft_addback_token(head, token);
}

t_token	*ft_token_builder(t_ms *ms)
{
	t_token	*head;

	head = NULL;
	while (ms->buffer && *ms->buffer)
	{
		ft_build_token_list(ms, &head);
		if (ms->buffer && *ms->buffer)
			ms->buffer++;
	}
	return (head);
}

t_token *ft_create_subshell_token(t_ms *ms_sub, t_token *token, size_t index)
{
	t_token	*subshell_token;
	t_token	*tmp;

	subshell_token = NULL;
	if (token->type == PARENTHESIS)
	{
		ms_sub->buffer = token->token;
		ms_sub->buffer_start = token->token;
		subshell_token = ft_token_builder(ms_sub);
		tmp = subshell_token;
		while (tmp)
		{
			tmp->subshell_id = index;
			tmp = tmp->next;
		}
	}
	return (subshell_token);
}

void	ft_expand_subshell_token_list(t_token **head, t_token **token_l)
{
	size_t	index;
	t_token	*subshell_token_l;
	t_ms	ms_sub;
	index = 0;

	subshell_token_l = ft_create_subshell_token(&ms_sub, *token_l, index);
	if (subshell_token_l)
	{
		if ((*token_l)->prev && !ft_has_operator((*token_l)->prev->type))
 			exit(1);
		if ((*token_l)->prev)
			(*token_l)->prev->next = subshell_token_l;
		else
			*head = subshell_token_l;
		subshell_token_l->prev = (*token_l)->prev;
		subshell_token_l = ft_find_last_token(subshell_token_l);
		if ((*token_l)->next)
			(*token_l)->next->prev = subshell_token_l;
		subshell_token_l->next = (*token_l)->next;
		ft_delete_token((*token_l));
		index++;
		(*token_l) = subshell_token_l->prev;
	}
}

void	ft_build_subshell_token_list(t_token **head, int has_subshell)
{
	t_token	*token_l;

	if (!head || !*head || has_subshell == FALSE)
		return ;
	token_l = *head;
	while (token_l)
	{
		ft_expand_subshell_token_list(head, &token_l);
		token_l = token_l->next;
	}
}

int	ft_tokenizer(t_ms *ms)
{
	ms->tokens = ft_token_builder(ms);
	//ft_build_subshell_token_list(&ms->tokens, ms->has_subshell);
	ft_find_variable_expression_and_replace(ms);
	return (SUCCESS_CODE);
}
