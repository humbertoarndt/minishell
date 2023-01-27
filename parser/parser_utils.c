/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:13:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/12 14:30:44 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_operator(t_token_type type)
{
	return (type == PIPELINE || type == AND_IF || type == OR_IF);
}

int	ft_has_redirect(t_token_type type)
{
	return (type == IO_FILE_TRUNCATE || type == IO_FILE_INFILE
		|| type == IO_FILE_APPEND || type == IO_HEREDOC);
}

void	ft_cmds_counter(t_ms *ms, t_executor *exec)
{
	if (!exec)
		return ;
	if (exec->cmds->argv_list)
		ms->ctr.cmds_count++;
	ft_cmds_counter(ms, exec->left);
	ft_cmds_counter(ms, exec->right);
}

t_redir_type	ft_convert_token_type_redir_type(t_token_type token_type)
{
	if (token_type == IO_FILE_APPEND)
		return (APPEND);
	if (token_type == IO_FILE_INFILE)
		return (INFILE);
	if (token_type == IO_FILE_TRUNCATE)
		return (TRUNCATE);
	if (token_type == IO_HEREDOC)
		return (HEREDOC);
	return (NOT_FOUND_REDIR);
}
