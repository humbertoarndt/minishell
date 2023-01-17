/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:22:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 22:45:35 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_variable_and_replace(t_ms *ms, char *str,
			char *var_expression)
{
	char		*to_replace;
	t_hash_item	*env_item;
	char		*replace_str;

	if (ft_strncmp(var_expression, VARIABLE_EXPRESSION,
			ft_strlen(var_expression)) == 0)
		replace_str = (ft_strdup(VARIABLE_EXPRESSION));
	else if (ft_strncmp(var_expression, QUESTION_VAR_EXPRESSION_STRING,
			ft_strlen(var_expression)) == 0)
		replace_str = ft_itoa(ms->exit_code);
	else
	{
		env_item = ft_search_item_by_key(ms->env.var, ++var_expression);
		if (env_item)
			to_replace = env_item->value;
		else
			to_replace = "";
		replace_str = ft_replace_str(str, --var_expression, to_replace);
	}
	return (replace_str);
}

void	ft_advance_str_ptr(char **str, char *start_var_expression,
			size_t len[2])
{
	while (*str != start_var_expression)
	{
		(*str)++;
		len[0]++;
	}
	while (str && (!ft_strchr(WHITE_SPACE, **str)
			&& !ft_strchr(SYMBOLS, **str)))
	{	
		(*str)++;
		len[1]++;
	}
}

char	*ft_replace_variable_expression(t_ms *ms, char *str)
{
	size_t		len[2];
	char		*replace_str;
	char		*var_expression;
	char		*start_var_expression;

	len[0] = 0;
	len[1] = 0;
	replace_str = NULL;
	start_var_expression = ft_strchr(str, VARIABLE_EXPRESSION[0]);
	if (!start_var_expression)
		return (NULL);
	ft_advance_str_ptr(&str, start_var_expression, len);
	var_expression = ft_substr(str - len[1], 0, len[1]);
	replace_str = ft_extract_variable_and_replace(ms, str - len[0] - len[1],
			var_expression);
	ft_free_ptr((void **)&(var_expression));
	return (replace_str);
}

void	ft_find_variable_expression_and_replace(t_ms *ms)
{
	char	*new_str;
	t_token	*head_token;

	head_token = ms->tokens;
	while (head_token)
	{
		if (head_token->should_expand)
		{
			while (TRUE)
			{
				new_str = ft_replace_variable_expression(ms, head_token->token);
				if (!new_str)
					break ;
				ft_free_ptr((void **)&(head_token->token));
				head_token->token = new_str;
				if (ft_strncmp(new_str, VARIABLE_EXPRESSION,
						ft_strlen(new_str)) == 0)
					break ;
			}
		}
		head_token = head_token->next;
	}
}
