/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:12:20 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/26 20:34:17 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int	ft_keep_literal_string(char *line, char quoting_char, int *index)
{
	int i;
	int	found_quoting_char;

	i = *index;
	found_quoting_char = FALSE;
	if (line[i] == quoting_char)
	{
		line[i] = SENTINEL_CHAR;
		while (line[i] && line[i] != quoting_char)
			i++;
		line[i] = SENTINEL_CHAR;
		found_quoting_char = TRUE;
	}
	*index = i;
	return (found_quoting_char);
}

void	ft_replace_whitespace_by_sentinel_char(char *line, char *delimiters)
{
	int		i;

	i = 0;
	while (line[i])
	{
		ft_keep_literal_string(line, SINGLE_QUOTE_CHAR, &i);
		ft_keep_literal_string(line, DOUBLE_QUOTE_CHAR, &i);
		if (ft_strchr(delimiters, line[i]))
			line[i]= SENTINEL_CHAR;
		i++;
	}
}

char	**ft_tokenizer(char *line)
{
	char	**split_line;
	ft_replace_whitespace_by_sentinel_char(line, WHITE_SPACE);
	split_line = ft_split(line, SENTINEL_CHAR);
	return (split_line);
}
