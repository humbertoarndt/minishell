/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:28:39 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/23 23:07:18 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_argc_argc(int argc, char *argv[])
{
	if (argc > 1 && argv)
	{
		print_custom_arg_error(TO_MANY_ARGUMENTS_ARG,
			TO_MANY_ARGUMENTS_ERROR_MSG);
		return (ERROR_CODE);
	}
	return (SUCCESS_CODE);
}

void	ft_print_custom_error_and_exit(t_ms *ms, char *argv, char *message,
			int exit_code)
{
	ft_restore_stdin_out(ms);
	print_custom_arg_error(argv, message);
	ft_free_all_ms(ms);
	exit(exit_code); // trocar pelo próprio exit
}

void	ft_print_error_and_exit(t_ms *ms, char *arg_err, int exit_code)
{
	ft_restore_stdin_out(ms);
	print_custom_arg_error(arg_err, strerror(exit_code));
	ft_free_all_ms(ms);
	exit(ms->exit_code); // trocar pelo próprio exit
}

void	ft_print_syntax_error(t_ms *ms)
{
	char	*error_message;

	error_message = ft_syntax_error_message(ms->buffer);
	print_custom_arg_error(NULL, error_message);
	ft_free_ptr((void **)&error_message);
	ft_free_all_ms(ms); // mudar para free_ms (não precisa sair do programa, so começar de novo)
}