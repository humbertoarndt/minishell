/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:29:22 by harndt            #+#    #+#             */
/*   Updated: 2022/10/28 18:41:02 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;

	(void)envp;
	if (ft_check_argc_argc(argc, argv))
		return (ERROR_CODE);
	ft_prompt(&ms);
	return (SUCCESS_CODE);
}