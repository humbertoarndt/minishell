/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:28:38 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/22 16:35:23 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_found_redirection(char *buffer)
{
	if (ft_strncmp(buffer, GREAT, ft_strlen(GREAT)) == 0
		&& ft_strncmp(buffer, DGREAT, ft_strlen(DGREAT)))
		return (IO_FILE_TRUNCATE);
	else if (ft_strncmp(buffer, LESS, ft_strlen(LESS)) == 0
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

t_token	*ft_create_io_file_token_with_quote(t_ms *ms, t_token_type type,
			size_t *len)
{
	t_token			*io_file;

	if (ft_strncmp(ms->buffer, EMPTY_DOUBLE_QUOTE, 2) == 0
		|| ft_strncmp(ms->buffer, EMPTY_SINGLE_QUOTE, 2) == 0)
	{
		ms->buffer = ms->buffer + 2;
		*len = *len + 2;
		return (NULL);
	}
	io_file = ft_quoting_tokenizer(ms);
	if (!io_file)
		return (NULL);
	io_file->type = type;
	return (io_file);
}

t_token	*ft_filename_parser_quote(t_ms *ms, t_token_type type, size_t *len)
{
	t_token			*io_file;

	while (!ft_strchr(WHITE_SPACE, *ms->buffer)
		&& !ft_found_redirection(ms->buffer)
		&& !ft_strchr(OPERATORS, *ms->buffer))
	{
		if (ft_is_invalid_file(ms))
			return (NULL);
		io_file = ft_create_io_file_token_with_quote(ms, type, len);
		if (io_file)
			return (io_file);
		*len = *len + 1;
		ms->buffer++;
	}
	return (NULL);
}

t_token	*ft_io_file_tokenizer(t_ms *ms)
{
	t_token			*io_file;
	t_token_type	type;
	char			*tok;
	size_t			len;

	io_file = NULL;
	len = 0;
	type = ft_found_redirection(ms->buffer);
	ft_advance_after_io_symbol(&ms->buffer, type);
	ft_advance_ptr_after_white_space(&ms->buffer);
	if (ft_is_invalid_file(ms))
		return (NULL);
	io_file = ft_filename_parser_quote(ms, type, &len);
	if (io_file)
		return (io_file);
	tok = ft_create_token_string(ms, len);
	ft_remove_empty_quoting(&tok, EMPTY_DOUBLE_QUOTE);
	ft_remove_empty_quoting(&tok, EMPTY_SINGLE_QUOTE);
	io_file = ft_create_token_node(tok, type);
	ft_advance_ptr_after_white_space(&ms->buffer);
	return (io_file);
}
