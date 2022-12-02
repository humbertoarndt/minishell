/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:45 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/01 23:29:53 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_executor	*ft_parser(t_ms *ms);

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

void	ft_set_is_subshell(t_executor *exec_tree)
{
	if (!exec_tree)
		return ;
	exec_tree->is_subshell = TRUE;
	ft_set_is_subshell(exec_tree->left);
	ft_set_is_subshell(exec_tree->right);
}

void	ft_add_subshell(t_executor *current_tree, t_token *token_head, t_ms *ms)
{
	t_ms		ms_sub;
	t_token		*subshell_token_l;
	t_executor	*subshell_tree;
	size_t		index;

	if (!current_tree || !token_head)
		return ;
	index = 0;
	ms->ctr.subshell_count++;
	ms_sub.ctr.index = 0;
	subshell_token_l = ft_create_subshell_token(&ms_sub, token_head, index);
	ms_sub.tokens = subshell_token_l;
	subshell_tree = ft_parser(&ms_sub);
	subshell_tree->root = current_tree;
	ft_set_is_subshell(subshell_tree);
	if (!current_tree->subshell)
	{
		current_tree->subshell = subshell_tree;
		return ;
	}
	subshell_tree->subshell = current_tree->subshell;
	current_tree->subshell = subshell_tree;
	subshell_tree->subshell = NULL;
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
	else if (token_head->type == PARENTHESIS)
		ft_add_subshell(current_tree, token_head, ms);
	else
		ft_add_command_list(current_tree, token_head, ms);
}

void	ft_add_subshell_root(t_executor *final_tree)
{
	t_executor	*last_subshell;

	if (!final_tree)
		return ;
	last_subshell = final_tree->subshell;
	while (last_subshell && last_subshell->subshell)
	{
		last_subshell = last_subshell->subshell;
	}
	if (last_subshell)
		last_subshell->subshell_root = final_tree->root;
	ft_add_subshell_root(final_tree->left);
	ft_add_subshell_root(final_tree->right);
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
	//ft_add_subshell_root(final_tree);
	return (final_tree);
}
