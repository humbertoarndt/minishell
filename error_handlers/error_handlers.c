/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:28:39 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/17 16:58:21 by bbonaldi         ###   ########.fr       */
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
	ft_free_all_ms(ms, TRUE);
	exit(exit_code); // trocar pelo próprio exit
}
	
void	ft_print_custom_error_and_exit2(t_ms *ms, char *argv[2], char *message,
			int exit_code)
{
	char	*concat_argv;

	concat_argv = ft_strjoin(argv[0], argv[1]);
	ft_restore_stdin_out(ms);
	print_custom_arg_error(concat_argv, message);
	ft_free_ptr((void **)&concat_argv);
	ft_free_all_ms(ms, TRUE);
	exit(exit_code); // trocar pelo próprio exit
}

void	ft_print_error_and_exit(t_ms *ms, char *arg_err, int exit_code)
{
	ft_restore_stdin_out(ms);
	print_custom_arg_error(arg_err, strerror(exit_code));
	ft_free_all_ms(ms, TRUE);
	exit(ms->exit_code); // trocar pelo próprio exit
}


void	ft_print_syntax_error(t_ms *ms)
{
	char	*error_message;

	error_message = ft_syntax_error_message(ms->buffer);
	print_custom_arg_error(NULL, error_message);
	ft_free_ptr((void **)&error_message);
	ft_free_all_ms(ms, FALSE); // mudar para free_ms (não precisa sair do programa, so começar de novo)
}


void	ft_print_syntax_error_no_exit(t_ms *ms, char *token_error,
			int exit_code, t_error_type error_type)
{
	
	if (token_error)
		ms->buffer = token_error;
	ms->exit_code = exit_code;
	ms->invalid_program = error_type;
	ft_print_syntax_error(ms);
}