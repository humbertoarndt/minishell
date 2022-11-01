/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:48:56 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/27 22:10:17 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{
	ms->buffer = NULL;
	ms->buffer_start = NULL;
	ms->tokens = NULL;
	ms->invalid_program = FALSE;
	ms->exit_code = SUCCESS_CODE;
}