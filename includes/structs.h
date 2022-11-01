/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:28:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/28 17:53:34 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_error_type
{
	QUOTING_ERR = TRUE,
	MISSING_FILE_ERR,
	SYNTAX_ERR
}			t_error_type;

typedef enum e_token_type
{
	NOT_FOUND,
	WORD,
	IO_FILE_TRUNCATE,
	IO_FILE_APPEND,
	IO_FILE_INFILE,
	IO_HEREDOC,
	OR_IF,
	AND_IF,
	VAR_EXPRESSION,
	WILDCARD,
	PIPELINE,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}			t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_ms
{
	char				*buffer;
	char				*buffer_start;
	t_error_type		invalid_program;
	int					exit_code;
	t_token				*tokens;
}				t_ms;

#endif