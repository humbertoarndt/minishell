/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:22:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/01 23:03:51 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_variable_expression(t_ms *ms, char **buffer)
{
	char	*start_var_expression;
	char	*var_expression;
	size_t	len;

	len = 0;
	start_var_expression = ft_strchr(*buffer, VARIABLE_EXPRESSION[0]);
	if (start_var_expression)
	{
		while (*buffer && (!ft_strchr(WHITE_SPACE, **buffer)
			|| !ft_strchr(SYMBOLS, **buffer)))
		{	
			(*buffer)++;
			len++;
		}
		var_expression = ft_create_token_string(ms, len);
	}
	return (var_expression);
}