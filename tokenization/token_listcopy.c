/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list copy 2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:58:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/29 23:21:38 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_tokens(t_token **token_head);

t_token	*ft_find_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_token	*ft_create_token_node(char *token, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = type;
	new_token->token = token;
	new_token->should_expand = TRUE;
	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->subshell_id = -1;
	return (new_token);
}

void	ft_addback_token(t_token **head, t_token *new_token)
{
	t_token	*last_token;

	if (!(*head))
	{
		*head = new_token;
		return ;
	}
	last_token = ft_find_last_token(*head);
	last_token->next = new_token;
	new_token->prev = last_token;
}

void	ft_add_front_subshell(t_token *token, t_token *subshell_token)
{
	if (!(token)->subshell)
		token->subshell = subshell_token;
	else
	{
		subshell_token->subshell = token->subshell;
		token->subshell = subshell_token;
	}
}


void	ft_delete_subshells_token(t_token **token_head)
{
	t_token	*last_subshell;
	t_token	*tmp;

	if (!token_head || !*token_head)
		return ;
	last_subshell = (*token_head)->subshell;
	while (last_subshell)
	{
		tmp = last_subshell->subshell;
		ft_clear_tokens(&last_subshell);
		last_subshell = tmp;
	}
}

void	ft_delete_token(t_token *token, int delete_shubshell)
{
	if (token && token->token)
	{
		ft_free_ptr((void **)&(token->token));
		ft_free_ptr((void **)&(token));
		if (delete_shubshell)
			ft_delete_subshells_token(&token);
		token = NULL;
	}
}

void	ft_clear_tokens(t_token **token_head)
{
	t_token	*token_tmp;

	if (!*token_head || !token_head)
		return ;
	while (*token_head)
	{
		if (!(*token_head)->next)
		{
			ft_delete_token(*token_head, TRUE);
			break ;
		}
		token_tmp = (*token_head)->next;
		token_tmp->prev = NULL;
		ft_delete_token(*token_head, TRUE);
		(*token_head) = token_tmp;
	}
	token_head = NULL;
}
