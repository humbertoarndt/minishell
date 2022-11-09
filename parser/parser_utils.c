/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:13:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/08 22:15:51 by bbonaldi         ###   ########.fr       */
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