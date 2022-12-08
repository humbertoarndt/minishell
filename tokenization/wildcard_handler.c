/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:12:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 20:04:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_all_dirs()
{
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d)
	{
		while (TRUE)
  		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			ft_printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return ;
}

// char	**ft_find_template_str(char *str)
// {
// 	char	**split_wild_card;

// 	split_wild_card = ft_split(str, '*');
// 	if (!split_wild_card)
// 		return (NULL);
	
	
// }


void	ft_find_wildcard_and_replace(t_ms *ms)
{
	// char	*new_str;
	// t_token	*head_token;

	// head_token = ms->tokens;
	// while (head_token)
	// {
	// 	if (head_token->type != DOUBLE_QUOTE && head_token->type != SINGLE_QUOTE)
	// 	{
	// 		while (TRUE)
	// 		{
	// 			new_str = ft_replace_variable_expression(ms, head_token->token);
	// 			if (!new_str)
	// 				break ;
	// 			ft_free_ptr((void **)&(head_token->token));
	// 			head_token->token = new_str;
	// 			if (ft_strncmp(new_str, VARIABLE_EXPRESSION,
	// 					ft_strlen(new_str)) == 0)
	// 				break ;
	// 		}
	// 	}
	// 	head_token = head_token->next;
	// }
	ft_printf("", ms);
	ft_list_all_dirs();
}
