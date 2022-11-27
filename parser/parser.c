/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:45 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/27 19:20:30 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_file(t_executor *current_tree, t_token *token_head)
{
	t_file			*file;
	t_redir_type	redir_type;
	t_list			*list_file;

	redir_type = ft_convert_token_type_redir_type(token_head->type);
	file = ft_init_file(redir_type, token_head->token);
	list_file = ft_lstnew(file);
	ft_lstadd_back(&current_tree->files, list_file);
}

void	ft_add_command_list(t_executor *current_tree, t_token *token_head,
			t_ms *ms)
{
	t_list			*list_argv;
	char			*token;

	token = ft_strdup(token_head->token);
	list_argv = ft_lstnew(token);
	ft_lstadd_back(&current_tree->cmds->argv_list, list_argv);
	if (current_tree->cmds->argv_list && 
		current_tree->cmds->argv_list->next == NULL)
		current_tree->cmds->cmd_index = ms->ctr.index++;
}

t_executor	*ft_set_executor(t_token *tokens,
			t_executor **current_tree)
{
	t_executor	*parent_tree;

	parent_tree = ft_init_tree();
	if ((*current_tree)->root)
	{
		parent_tree->left = (*current_tree)->root;
		(*current_tree)->root->root = parent_tree;
	}
	else
	{
		(*current_tree)->root = parent_tree;
		parent_tree->left = *current_tree;
	}
	(*current_tree)->root = parent_tree;
	parent_tree->operator = ft_strdup(tokens->token);
	parent_tree->right = ft_init_tree();
	parent_tree->right->root = parent_tree;
	*current_tree = parent_tree->right;
	return (parent_tree);
}

void	ft_build_commands_and_fds_tree(t_token *token_head,
			t_executor *current_tree, t_ms *ms)
{
	if (ft_has_redirect(token_head->type))
		ft_add_file(current_tree, token_head);
	else
		ft_add_command_list(current_tree, token_head, ms);
}

t_executor	*ft_parser(t_ms *ms)
{
	t_executor	*current_tree;
	t_executor	*final_tree;
	t_token		*token_head;

	current_tree = ft_init_tree();
	final_tree = current_tree;
	ms->ctr.index = 0;
	token_head = ms->tokens;
	while (token_head)
	{
		if (ft_has_operator(token_head->type))
			final_tree = ft_set_executor(token_head, &current_tree);
		else
			ft_build_commands_and_fds_tree(token_head, current_tree, ms);
		token_head = token_head->next;
	}
	ft_cmds_counter(ms, final_tree);
	return (final_tree);
}
