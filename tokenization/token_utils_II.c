/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:16:52 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:47:46 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_advance_str_ptr_exp_handler(char **str, char *start_var_expression,
			size_t len[2])
{
	while (*str != start_var_expression)
	{
		(*str)++;
		len[0]++;
	}
	while (str && (!ft_strchr(WHITE_SPACE, **str)
			&& !ft_strchr(SYMBOLS, **str)) && !ft_strchr(QUOTING, **str))
	{
		(*str)++;
		len[1]++;
		if (**str == VARIABLE_EXPRESSION[0])
			break ;
	}
	return (*str);
}

char	*ft_replace_question_variable_expression(t_ms *ms, char *str)
{
	char		*to_replace;
	char		*replace_str;

	to_replace = ft_itoa(ms->exit_code);
	replace_str = ft_replace_str(str, QUESTION_EXP_STR, to_replace);
	ft_free_ptr((void **)&to_replace);
	return (replace_str);
}

int	ft_is_invalid_file(t_ms *ms)
{
	if (ft_strchr(SYMBOLS, *ms->buffer) || !*ms->buffer)
	{
		ft_print_syntax_error_no_exit(ms, NULL, 2, MISSING_FILE_ERR);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_update_buffer(t_ms *ms, char **line_acc)
{
	size_t	index;

	index = 0;
	index = ms->buffer - ms->buffer_start;
	ms->buffer_start = ft_strjoin_free(ms->buffer_start, *line_acc);
	ms->buffer = ms->buffer_start;
	while (index)
	{	
		ms->buffer++;
		index--;
	}
}
