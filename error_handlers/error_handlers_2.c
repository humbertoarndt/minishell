/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:28:39 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:08:25 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_syntax_error_no_exit(t_ms *ms, char *token_error,
			int exit_code, t_error_type error_type)
{
	if (token_error)
		ms->buffer = token_error;
	ft_set_syntax_error_and_exit_code(ms, error_type, exit_code);
	ft_print_syntax_error(ms);
}

void	ft_print_error_and_invalid_program(t_ms *ms, char *arg_err)
{
	ft_restore_stdin_out(ms);
	print_custom_arg_error(arg_err, strerror(errno));
	ms->invalid_program = SYNTAX_ERR;
}
