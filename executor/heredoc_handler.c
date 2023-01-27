/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 10:55:09 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_deal_expansion_heredoc(t_ms *ms, char *line)
// {
// 	int		count_dollar_sign;
// 	char	*line_with_var_exp;
// 	char	**free_ptrs;
// 	int		index;

// 	count_dollar_sign = ft_count_char(line, VARIABLE_EXPRESSION[0]);
// 	if (count_dollar_sign == 0)
// 		return (ft_strdup(line));
// 	index = 0;
// 	line_with_var_exp = line;
// 	free_ptrs = (char **)malloc(sizeof(char *) * count_dollar_sign);
// 	while (index < count_dollar_sign)
// 	{
// 		line_with_var_exp = ft_replace_variable_expression(ms,
// 				line_with_var_exp, line_with_var_exp);
// 		free_ptrs[index] = line_with_var_exp;
// 		index++;
// 	}
// 	while (--count_dollar_sign)
// 		ft_free_ptr((void **)&free_ptrs[count_dollar_sign - 1]);
// 	free(free_ptrs);
// 	free_ptrs = NULL;
// 	return (line_with_var_exp);
// }

t_bool	ft_control_c_handler(t_ms *ms)
{
	if (g_status.paused)
	{
		g_status.paused = FALSE;
		ft_set_syntax_error_and_exit_code(ms, SYNTAX_ERR, 130);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_print_heredoc_control_d(char *delimeter)
{
	int	fd_std_out;

	fd_std_out = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("minishell: warning here-document delimited by" \
			" end-of-file (wanted `%s')\n", delimeter);
	dup2(fd_std_out, STDOUT_FILENO);
	close(fd_std_out);
}

char	*ft_line_accumulator(t_ms *ms, t_file *file, char *del_with_nl)
{
	char	*line;
	char	*line_acc;

	line_acc = ft_strdup("");
	while (TRUE)
	{
		ft_printf(HEREDOC_START);
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, del_with_nl) == 0 || !line || g_status.paused)
		{
			if (!line && g_status.paused == FALSE)
				ft_print_heredoc_control_d(file->delimeter);
			ft_free_ptr((void **)&(line));
			if (ft_control_c_handler(ms))
			{
				ft_free_ptr((void **)&line_acc);
				return (NULL);
			}
			break ;
		}
		line_acc = ft_strjoin_free(line_acc, line);
		ft_replace_variable_expression_all(ms, &line_acc);
	}
	return (line_acc);
}

void	ft_heredoc_handler(t_ms *ms, t_file *file)
{
	char	*line_acc;
	char	*delimeter_with_nl;

	set_heredoc_signals();
	file->fd = open(file->file, O_TRUNC | O_CREAT | O_RDWR, DEFAULT_PERMISSION);
	delimeter_with_nl = ft_strjoin(file->delimeter, "\n");
	line_acc = ft_line_accumulator(ms, file, delimeter_with_nl);
	if (line_acc)
	{
		ft_putstr_fd(line_acc, file->fd);
		ft_free_ptr((void **)&line_acc);
	}
	ft_close_fd(file->fd);
	ft_free_ptr((void **)&(delimeter_with_nl));
}
