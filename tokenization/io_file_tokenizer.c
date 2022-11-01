/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:28:38 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/28 00:06:33 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_redirection(char *buffer)
{
	if (ft_strncmp(buffer, GREAT, ft_strlen(GREAT)) == 0
		&& ft_strncmp(buffer, DGREAT, ft_strlen(DGREAT)))
		return (IO_FILE_TRUNCATE);
	else if(ft_strncmp(buffer, LESS, ft_strlen(LESS)) == 0
			&& ft_strncmp(buffer, DLESS, ft_strlen(DLESS)))
		return (IO_FILE_INFILE);
	else if (ft_strncmp(buffer, DGREAT, ft_strlen(DGREAT)) == 0)
		return (IO_FILE_APPEND);
	return (NOT_FOUND);
}

void	ft_advance_after_io_symbol(char **buffer, t_token_type type)
{
	if (type == NOT_FOUND)
		return ;
	if (type == IO_FILE_APPEND)
		*buffer = (*buffer + 2);
	else
		(*buffer)++;
}

int	ft_is_invalid_file(t_ms *ms)
{
	if (ft_strchr(SYMBOLS, *ms->buffer) || !*ms->buffer
		|| ft_found_quoting(ms->buffer))
	{
		ms->invalid_program = MISSING_FILE_ERR;
		return (TRUE);
	}
	return (FALSE);
}

t_token	*ft_io_file_tokenizer(t_ms *ms)
{
	t_token			*io_file;
	t_token_type	type;
	char			*tok;
	size_t			len;
	
	len = 0;
	type = ft_found_redirection(ms->buffer);
	ft_advance_after_io_symbol(&ms->buffer, type);
	ft_advance_ptr_after_white_space(&ms->buffer);
	while (!ft_strchr(WHITE_SPACE, *ms->buffer))
	{
		if (ft_is_invalid_file(ms))
			return (NULL);
		len++;
		ms->buffer++;
	}
	tok = ft_create_token_string(ms, len);
	io_file = ft_create_token_node(tok, type);
	return (io_file);
}