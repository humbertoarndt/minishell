/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:58:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/27 21:35:41 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_token->prev = NULL;
	new_token->next = NULL;
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

void	ft_delete_token(t_token *token)
{
	if (token && token->token)
	{
		free(token->token);
		free(token);
		token = NULL;
	}
}

void	ft_clear_tokens(t_token **token_head)
{
	t_token	*token_tmp;

	
	while (*token_head)
	{
		if (!(*token_head)->next)
		{
			ft_delete_token(*token_head);
			return ;
		}
		token_tmp = (*token_head)->next;
		token_tmp->prev = NULL;
		ft_delete_token(*token_head);
		(*token_head) = token_tmp;
	}
	token_head = NULL;
}