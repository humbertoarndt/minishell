/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/08 20:21:23 by bbonaldi         ###   ########.fr       */
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
	char	*delimeter_with_nl;

	set_heredoc_signals();
	line_acc = ft_strdup("");
	file->fd = open(file->file, O_TRUNC | O_CREAT | O_RDWR, DEFAULT_PERMISSION);
	delimeter_with_nl = ft_strjoin(file->delimeter, "\n");
	while (TRUE)
	{
		ft_printf(HEREDOC_START);
		line = ft_get_next_line(0);
		if (ft_strcmp(line, delimeter_with_nl) == 0 || !line || g_status.paused == TRUE)
		{
			if (!line && g_status.paused == FALSE)
				ft_printf("minishell: warning here-document delimited by" \
			" end-of-file (wanted `%s')\n", file->delimeter);
			ft_free_ptr((void **)&(line));
			if (g_status.paused == TRUE)
			{
				g_status.paused = FALSE;
				ms->exit_code = 130;
				ms->invalid_program = 2;
				return ;
			}
			break ;
		}
		line_acc = ft_strjoin_free(line_acc, line);
		line_acc = ft_deal_expansion_heredoc(ms, line_acc);
	}
	ft_putstr_fd(line_acc, file->fd);
	ft_close_fd(file->fd);
	ft_free_ptr((void **)&(line_acc));
	ft_free_ptr((void **)&(delimeter_with_nl));
}
