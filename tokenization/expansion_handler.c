/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:22:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:22:01 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_variable_and_replace(t_ms *ms, char *str,
			char *var_expression, char *original_str)
{
	char		*to_replace;
	t_hash_item	*env_item;
	char		*replace_str;

	if (ft_strcmp(var_expression, VARIABLE_EXPRESSION) == 0
		&& ft_strcmp(original_str, VARIABLE_EXPRESSION) == 0)
		replace_str = (ft_strdup(VARIABLE_EXPRESSION));
	else if (ft_strcmp(var_expression, VARIABLE_EXPRESSION) == 0
		&& ft_strcmp(original_str, VARIABLE_EXPRESSION))
		return (ft_strdup(original_str));
	else if (ft_strnstr(var_expression, QUESTION_EXP_STR,
			ft_strlen(var_expression)))
		replace_str = ft_replace_question_variable_expression(ms, str);
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

char	*ft_find_start_var_expression(char *str)
{
	while (*str)
	{
		if (*str == VARIABLE_EXPRESSION[0])
		{
			++str;
			if (*str == VARIABLE_EXPRESSION[0] || ft_strchr(WHITE_SPACE, *str))
				continue ;
			else
				return (--str);
		}
		str++;
	}
	return (NULL);
}

char	*ft_replace_variable_expression(t_ms *ms, char *token_original,
			char *str)
{
	size_t		len[2];
	char		*replace_str;
	char		*var_expression;
	char		*start_var_expression;

	len[0] = 0;
	len[1] = 0;
	replace_str = NULL;
	start_var_expression = ft_find_start_var_expression(str);
	if (!start_var_expression)
		return (NULL);
	ft_advance_str_ptr_exp_handler(&str, start_var_expression, len);
	var_expression = ft_substr(str - len[1], 0, len[1]);
	replace_str = ft_extract_variable_and_replace(ms, str - len[0] - len[1],
			var_expression, token_original);
	ft_free_ptr((void **)&(var_expression));
	return (replace_str);
}

void	ft_replace_variable_expression_all(t_ms *ms, char **token)
{
	char	*new_str;

	while (TRUE)
	{
		new_str = ft_replace_variable_expression(ms, *token, *token);
		if (!new_str)
			break ;
		ft_free_ptr((void **)&(*token));
		*token = new_str;
		if (ft_strcmp(new_str, VARIABLE_EXPRESSION) == 0)
			break ;
	}
}

void	ft_find_variable_expression_and_replace(t_ms *ms)
{
	t_token	*head_token;

	head_token = ms->tokens;
	while (head_token)
	{
		if (head_token->should_expand)
			ft_replace_variable_expression_all(ms, &head_token->token);
		head_token = head_token->next;
	}
}
