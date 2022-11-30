/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:12:20 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/29 23:21:38 by bbonaldi         ###   ########.fr       */
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

t_token *ft_create_subshell_token(t_ms *ms_sub, t_token *token)
{
	t_token	*subshell_token;

	subshell_token = NULL;
	if (token->type == PARENTHESIS)
	{
		ms_sub->buffer = token->token;
		ms_sub->buffer_start = token->token;
		subshell_token = ft_token_builder(ms_sub);
	}
	return (subshell_token);
}

void	ft_build_subshell_token_list(t_token **head, int has_subshell)
{
	t_token	*token_l;
	t_ms	ms_sub;
	t_token	*subshell_token;
	t_token	*tmp;

	if (!head || !*head || has_subshell == FALSE)
		return ;
	token_l = ft_find_last_token(*head);
	if (token_l == *head)
	{
		subshell_token = ft_create_subshell_token(&ms_sub, *head);
		ft_clear_tokens(head);
		*head = subshell_token;
		return ;
	}
	while (token_l)
	{
		subshell_token = ft_create_subshell_token(&ms_sub, token_l);
		if (subshell_token)
		{
			tmp = token_l->prev;
			if (tmp && !ft_has_operator(tmp->type))
				exit(1); //implementar error handler, syntax error
			if (!tmp)
			{
				token_l->type = SUBSHELL;
				ft_add_front_subshell(token_l, subshell_token);
			}
			else
			{
				tmp->next = token_l->next;
				if (token_l->next)
					token_l->next->prev =  tmp;
				//ft_add_front_subshell(token_l->subshell, subshell_token);
				ft_delete_token(token_l, TRUE);
				ft_add_front_subshell(tmp, subshell_token);
				token_l = tmp;
			}
		}
		token_l = token_l->prev;
		//implement logic if token list has multiple tokens
	}
}


int	ft_tokenizer(t_ms *ms)
{
	ms->tokens = ft_token_builder(ms);
	ft_build_subshell_token_list(&ms->tokens, ms->has_subshell);
	ft_find_variable_expression_and_replace(ms);
	return (SUCCESS_CODE);
}
