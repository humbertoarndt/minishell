/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:22:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/07 20:16:28 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_variable_and_replace(t_ms *ms, char *str, size_t len)
{
	char		*to_replace;
	t_hash_item	*env_item;
	char		*var_expression;
	char		*replace_str;

	var_expression = ft_substr(str - len, 0, len);
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
		replace_str = ft_replace_str(str - len, --var_expression, to_replace);
	}
	ft_free_ptr((void **)&(var_expression));
	return (replace_str);
}

char	*ft_replace_variable_expression(t_ms *ms, char *str)
{
	size_t		len;
	char		*replace_str;

	len = 0;
	replace_str = NULL;
	while (str && (!ft_strchr(WHITE_SPACE, *str) && !ft_strchr(SYMBOLS, *str)))
	{	
		str++;
		len++;
	}
	replace_str = ft_extract_variable_and_replace(ms, str, len);
	return (replace_str);
}

void	ft_find_variable_expression_and_replace(t_ms *ms)
{
	char	*start_var_expression;
	char	*new_str;
	t_token	*head_token;

	head_token = ms->tokens;
	while (head_token)
	{
		if (head_token->type != SINGLE_QUOTE)
		{
			while (TRUE)
			{
				start_var_expression = ft_strchr(head_token->token,
						VARIABLE_EXPRESSION[0]);
				if (!start_var_expression)
					break ;
				new_str = ft_replace_variable_expression(ms, head_token->token);
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
