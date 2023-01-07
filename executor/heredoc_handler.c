/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/07 16:07:18 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_deal_expansion_heredoc(t_ms *ms, char *line)
{
	int		count_dollar_sign;
	char	*line_with_var_exp;
	char	**free_ptrs;
	int		index;

	count_dollar_sign = ft_count_char(line, VARIABLE_EXPRESSION[0]);
	if (count_dollar_sign == 0)
		return (ft_strdup(line));
	index = 0;
	line_with_var_exp = line;
	free_ptrs = (char **)malloc(sizeof(char *) * count_dollar_sign);
	while (index < count_dollar_sign)
	{
		line_with_var_exp = ft_replace_variable_expression(ms,
				line_with_var_exp);
		free_ptrs[index] = line_with_var_exp;
		index++;
	}
	while (--count_dollar_sign)
		ft_free_ptr((void **)&free_ptrs[count_dollar_sign - 1]);
	free(free_ptrs);
	free_ptrs = NULL;
	return (line_with_var_exp);
}

void	ft_heredoc_handler(t_ms *ms, t_file *file)
{
	char	*line;
	char	*line_acc;
	char	*line_acc_with_nl;
	int		exit_status;

	line_acc = ft_strdup("");
	//novo
	pid_t pid_child = fork();
	
	if (pid_child == 0)
	{
		set_heredoc_signals(pid_child);
		file->fd = open(file->file, O_TRUNC | O_CREAT | O_RDWR, DEFAULT_PERMISSION);
		while (TRUE)
		{
			if (g_status.paused == TRUE)
			{
				g_status.paused = FALSE;
				ft_free_ptr((void **)&(line_acc));
				ft_close_fd(file->fd);
				return ;
			}
			line = readline(HEREDOC_START);
			if (ft_strcmp(line, file->delimeter) == 0 || !line)
			{
				if (!line)
					ft_printf("minishell: warning here-document delimited by" \
				" end-of-file (wanted `%s')\n", file->delimeter);
				ft_free_ptr((void **)&(line));
				break ;
			}
			line_acc = ft_strjoin_free(line_acc, line);
			line_acc_with_nl = ft_strjoin_free(line_acc, ft_strdup("\n"));
			line_acc = ft_deal_expansion_heredoc(ms, line_acc_with_nl);
			ft_free_ptr((void **)&(line_acc_with_nl));
		}
		ft_putstr_fd(line_acc, file->fd);
		ft_close_fd(file->fd);
		ft_free_ptr((void **)&(line_acc));
		exit_status = EXIT_SUCCESS;
		exit(0);
	}
	else
	{
		exit_status = ft_wait_child(pid_child);
		if (exit_status == 130)
		{
			ms->invalid_program = 2;
		}
	}
}
