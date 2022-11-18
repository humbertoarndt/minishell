/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:28:39 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/17 22:00:48 by bbonaldi         ###   ########.fr       */
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

void	ft_print_cmd_error_and_exit(t_ms *ms, t_executor *exec_tree)
{
	ft_restore_stdin_out(ms);
	print_custom_arg_error(exec_tree->cmds->argv[0],
		COMMAND_NOT_FOUND_ERROR_MSG);
	ft_free_all_ms(ms);
	exit(COMMAND_NOT_FOUND_ERROR_CODE); // trocar pelo próprio exit
}

void	ft_print_error_and_exit(t_ms *ms, char *arg_err,int exit_code)
{
	ft_restore_stdin_out(ms);
	perror(arg_err);
	ft_free_all_ms(ms);
	exit(exit_code); // trocar pelo próprio exit
}