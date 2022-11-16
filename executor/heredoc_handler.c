/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/15 23:12:12 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_heredoc_handler(t_ms *ms, t_file *file)
{
	char	*line;
	char	*line_acc;
	char	*line_with_var_exp;

	line_acc = ft_strdup("");
	file->fd = open(file->file, O_TRUNC | O_CREAT | O_RDWR, DEFAULT_PERMISSION);
	while (TRUE)
	{
		line = readline(HEREDOC_START);
		if (ft_strcmp(line, file->delimeter) == 0)
		{
			ft_free_ptr((void **)&(line));
			break ;
		}
		line_acc = ft_strjoin_free(line_acc, line);
		line_acc = ft_strjoin_free(line_acc, ft_strdup("\n"));
		line_with_var_exp = ft_replace_variable_expression(ms, line_acc);
		//expansion handler must work with several $ in the same line
		if (line_with_var_exp)
		{
			ft_free_ptr((void**)&(line_acc));
			line_acc = ft_strdup(line_with_var_exp);
		}
		ft_free_ptr((void**)&(line_with_var_exp));
	}
	ft_putstr_fd(line_acc, file->fd);
	ft_close_fd(file->fd);
	ft_free_ptr((void**)&(line_acc));
}